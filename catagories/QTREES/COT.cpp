#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("avx", "avx2")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
#ifdef tmd
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
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 100005;
const int MAXLG = __lg(MAXN) + 3;
const ll MOD = 1000000007;

int n, m, w[MAXN];
vector<int> wei, edge[MAXN];
pii qry[MAXN];
int k[MAXN];
int ans[MAXN];

vector<int> wnode[MAXN];

int in[MAXN], out[MAXN], dfs_clock, anc[MAXLG][MAXN], dep[MAXN];
void dfs_num (int nd, int par) {
    in[nd] = dfs_clock++;
    anc[0][nd] = par;
    dep[nd] = dep[par] + 1;
    for (auto v : edge[nd]) {
        if (v != par) {
            dfs_num(v, nd);
        }
    }
    out[nd] = dfs_clock++;
}

void build_anc () {
    for (int i=1;i<MAXLG; i++) {
        for (int j=1; j<=n; j++) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }
}

int lca (int u, int v) {
    if (dep[u] >= dep[v]) {
        swap(u, v);
    }
    for (int i=MAXLG-1; i>=0; i--) {
        if (dep[anc[i][v]] >= dep[u]) {
            v = anc[i][v];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i=MAXLG-1; i>=0; i--) {
        if (anc[i][u] != anc[i][v]) {
            u = anc[i][u];
            v = anc[i][v];
        }
    }
    return anc[0][u];
}

struct BIT {
    int bit[MAXN];
    int g[MAXN];
    void add (int x, int val) {
        g[x] += val;
        for (x++;x<MAXN;x+=-x&x) {
            bit[x] += val;
        }
    }

    int qry (int x) {
        int ret = 0;
        for (x++;x>0; x-=-x&x) {
            ret += bit[x];
        }
        return ret;
    }
} sum;

void add (int nd, int val) {
    sum.add(in[nd], val);
    sum.add(out[nd], -val);
}

int path (int u, int v) {
    int ca = lca(u, v);
    return sum.qry(in[u]) + sum.qry(in[v]) - sum.qry(in[ca])*2 + sum.g[in[ca]];

}

void pbs (vector<int> &id, int L, int R) {
    if (L == R - 1) {
        for (auto v : id) {
            ans[v] = R;
        }
    } else {
        int M = (L + R) >> 1;

        for (int i=L+1; i<=M; i++) {
            for (auto v : wnode[i]) {
                add(v, 1);
            }
        }

        vector<int> lid, rid;
        for (auto v : id) {
            int cnt = path(qry[v].X, qry[v].Y);
//            debug(v, cnt, k[v]);
            if (cnt >= k[v]) {
                lid.eb(v);
            } else {
                k[v] -= cnt;
                rid.eb(v);
            }
        }

        for (int i=L+1; i<=M; i++) {
            for (auto v : wnode[i]) {
                add(v, -1);
            }
        }

//        debug(L, R, M, lid, rid, id);
        pbs(lid, L, M);
        pbs(rid, M, R);
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP1 (i, n) {
        #ifdef tmd
        w[i] = rand();
        #else
        cin >> w[i];
        #endif // tmd
        wei.eb(w[i]);
    }
    sort(ALL(wei));
    wei.resize(unique(ALL(wei))-wei.begin());
    REP1 (i, n) {
        w[i] = lower_bound(ALL(wei), w[i])-wei.begin()+1;
        wnode[w[i]].eb(i);
    }
    debug("weied");

    REP (i, n-1) {
        int u, v;

        #ifdef tmd
        u = i + 2;
        v = rand() % (i+1) + 1;
        #else
        cin >> u >> v;
        #endif // tmd
        edge[u].eb(v);
        edge[v].eb(u);
    }

    dfs_num(1, 0);
    build_anc();

    debug("built");

    vector<int> id;
    REP (i, m) {
        #ifdef tmd
        qry[i].X = rand() % n + 1;
        qry[i].Y = rand() % n + 1;
        k[i] = 1;
        #else
        cin >> qry[i].X >> qry[i].Y >> k[i];
        #endif // tmd
        id.eb(i);
    }

    debug(0, SZ(wei)+1);
    pbs(id, 0, SZ(wei));
//    debug(wei);

    for (int i=0; i<m; i++) {
    #ifndef tmd
        cout << wei[ans[i]-1] << endl;
    #endif // tmd
    }
}
