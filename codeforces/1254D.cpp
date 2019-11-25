#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize ("unroll-loops")
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#ifdef tmd
#define TIME(i) Timer i(#i)
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
class Timer {
private:
    string scope_name;
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer (string name) : scope_name(name) {
        start_time = chrono::high_resolution_clock::now();
    }
    ~Timer () {
        auto stop_time = chrono::high_resolution_clock::now();
        auto length = chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
        double mlength = double(length) * 0.001;
        debug(scope_name, mlength);
    }
};
#else
#define TIME(i)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MOD = 998244353;
const int MAXN = 150005;
const int MAXLG = __lg(150005) + 1;
const int K = 300;

int sum[MAXN], pre[MAXN];

int qrySum (int x) {
    return pre[x];
}

void addRng (int l, int r, int dt) {
    sum[l] += dt;
    sum[r] += MOD-dt;
    if (sum[l] > MOD) {
        sum[l] -= MOD;
    }
    if (sum[r] > MOD) {
        sum[r] -= MOD;
    }
}

void buildSum () {
    for (int i=1; i<MAXN; i++) {
        sum[i] = sum[i-1] + sum[i];
        if (sum[i] >= MOD) {
            sum[i] -= MOD;
        }
        pre[i] = sum[i] + pre[i];
        if (pre[i] >= MOD) {
            pre[i] -= MOD;
        }
    }
}


ll mpow (ll bs, int ep) {
    ll ret = 1;
    while (ep) {
        if (ep & 1) {
            ret = ret * bs % MOD;
        }
        ep >>= 1;
        bs = bs * bs % MOD;
    }
    return ret;
}

int n, q, in[MAXN], out[MAXN], tme, sz[MAXN], anc[MAXLG][MAXN];
vector<int> edge[MAXN];
int invSZ;

void dfs (int nd, int par) {
    anc[0][nd] = par;
    in[nd] = tme++;
    sz[nd] = 1;
    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v, nd);
            sz[nd] += sz[v];
        }
    }
    out[nd] = tme;
}

void build_anc () {
    for (int i=1; i<MAXLG; i++) {
        for (int j=1; j<=n; j++) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }
}

bool uIsAncOfV (int u, int v) {
    return in[u] <= in[v] && out[v] <= out[u];
}

vector<pair<int,int> > ops;
int val[MAXN];

void addSubtree (int nd, int dt) {
    addRng(in[nd], out[nd], dt);
}

void flush_node () {
    REP1 (nd, n) {
        if (val[nd] == 0) {
            continue;
        }
        for (auto v : edge[nd]) {
            if (v != anc[0][nd]) {
                int ex = 1LL * val[nd] * sz[v] % MOD * invSZ % MOD;
                addSubtree(1, ex);
                addSubtree(v, MOD-ex);
            } else {
                int ex = 1LL * val[nd] * (sz[1]-sz[nd]) % MOD * invSZ % MOD;
                addSubtree(nd, ex);
            }
        }
        addSubtree(1, 1LL * val[nd] * invSZ % MOD);
        val[nd] = 0;
    }
}

void flush_ops () {
    for (auto v : ops) {
        val[v.first] += v.second;
        if (val[v.first] >= MOD) {
            val[v.first] -= MOD;
        }
    }

    memset(sum, 0, sizeof(sum));
    flush_node();
    buildSum();
}

void addNode (int nd, ll d) {
    ops.emplace_back(nd, d);
    if (ops.size() >= K) {
        flush_ops();
        ops.clear();
    }
}

int qryNode (int nd) {
    int ret = 0;
    for (auto op : ops) {
        // debug(op.first, op.second);
        if (op.first == nd) {
            ret += op.second;
        } else if (uIsAncOfV(op.first, nd)) {
            int lw = nd;
            for (int i=MAXLG-1; i>=0; i--) {
                if (!uIsAncOfV(anc[i][lw], op.first)) {
                    lw = anc[i][lw];
                }
            }
            ret += 1LL * op.second * (sz[1]-sz[lw]) % MOD * invSZ % MOD;
        } else {
            // debug("cross");
            ret += 1LL * op.second * sz[op.first] % MOD * invSZ % MOD;
        }
        if (ret >= MOD) {
            ret -= MOD;
        }
    }
    return (qrySum(in[nd]) + ret) % MOD;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    TIME(main);

    cin >> n >> q;
    tme = 1;
    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }
    dfs(1, 1);
    build_anc();
    invSZ = mpow(sz[1], MOD-2);

    while (q--) {
        int cmd, u, d;
        cin >> cmd >> u;
        if (cmd == 1) {
            cin >> d;
            addNode(u, d);
        } else {
            cout << qryNode(u) << endl;
        }
    }


}
