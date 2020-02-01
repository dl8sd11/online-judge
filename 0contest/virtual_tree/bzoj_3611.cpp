#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 1000006;
const ll MOD = 1000000007;
const int MAXLG = 21;
int dep[MAXN], anc[MAXLG][MAXN], n, q, in[MAXN], tim;

vector<int> edg[MAXN];

void dfs_anc (int nd, int par) {
    in[nd] = tim++;
    dep[nd] = dep[par] + 1;
    anc[0][nd] = par;
    for (auto v : edg[nd]) {
        if (v != par) {
            dfs_anc(v, nd);
        }
    }
}

void build_anc () {
    dfs_anc(1, 1);
    REP1 (i, MAXLG - 1) {
        REP1 (j, n) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }
}

int lca (int u, int v) {
    if (dep[u] > dep[v]) {
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
        if (anc[i][v] != anc[i][u]) {
            v = anc[i][v];
            u = anc[i][u];
        }
    }
    return anc[0][v];
}

bool is_imp[MAXN];
vector<int> vtree[MAXN], imp_vec;

void add_vedg (int f, int t) {
//    debug(f, t);
    vtree[f].emplace_back(t);
}

void build_virtual () {
    sort(imp_vec.begin(), imp_vec.end(), [](int a, int b) {
        return in[a] < in[b];
    });

    vector<int> stk = {1};
    vtree[1].clear();
    for (auto v : imp_vec) {
        int ca = lca(v, stk.back());
        if (stk.back() != ca) {
            while (dep[stk[SZ(stk)-2]] >= dep[ca]) {
                add_vedg(stk[SZ(stk)-2], stk.back());
                stk.pop_back();
            }
            if (stk.back() != ca) {
                vtree[ca].clear();
                add_vedg(ca, stk.back());
                stk.pop_back();
                stk.emplace_back(ca);
            }
        }
        vtree[v].clear();
        stk.emplace_back(v);
    }
    while (SZ(stk) >= 2) {
        add_vedg(stk[SZ(stk)-2], stk.back());
        stk.pop_back();
    }
}

ll sum;
int mn, mx, dpx[MAXN], dpn[MAXN];
ll sz[MAXN], sm[MAXN];
void solve (int nd) {
    dpx[nd] = sm[nd] = 0;
    dpn[nd] = MOD;
    sz[nd] = is_imp[nd];
    pii mxp = {0, 0}, mnp = {MOD, MOD};
    for (auto v : vtree[nd]) {
        if (v == 1) {
            continue;
        }
        solve(v);
        sz[nd] += sz[v];
        sm[nd] += sm[v] + sz[v] * (dep[v] - dep[nd]);
        if (sz[v] > 0) {
            dpx[nd] = max(dpx[nd], dpx[v] + dep[v] - dep[nd]);
            dpn[nd] = min(dpn[nd], dpn[v] + dep[v] - dep[nd]);
        }
        if (dpx[v]+dep[v]-dep[nd] > mxp.first) {
            mxp.second = mxp.first;
            mxp.first =dpx[v]+dep[v]-dep[nd];
        } else if (dpx[v]+dep[v]-dep[nd] > mxp.second) {
            mxp.second = dpx[v]+dep[v]-dep[nd];
        }
        if (dpn[v]+dep[v]-dep[nd] < mnp.first) {
            mnp.second = mnp.first;
            mnp.first =dpn[v]+dep[v]-dep[nd];
        } else if (dpn[v]+dep[v]-dep[nd] < mnp.second) {
            mnp.second = dpn[v]+dep[v]-dep[nd];
        }
    }
    if (mxp.second != 0) {
        mx = max(mx, mxp.first + mxp.second);
    }
    if (mnp.second != MOD) {
        mn = min(mn, mnp.first + mnp.second);
    }

    for (auto v : vtree[nd]) {
        sum +=  (sm[v] + sz[v] * ll(dep[v] - dep[nd])) * (sz[nd] - sz[v]);
    }

    if (is_imp[nd]) {
        mn = min(mn, dpn[nd]);
        mx = max(mx, dpx[nd]);
        dpn[nd] = 0;
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    #ifdef tmd
    n = 1000000;
    #else
    cin >> n;
    #endif

    REP (i, n-1) {
        int u, v;
        #ifdef tmd
        u = i+2, v = rand()%(i+1)+1;
        #else
        cin >> u >> v;
        #endif
        edg[u].emplace_back(v);
        edg[v].emplace_back(u);
    }

    build_anc();
    debug("built");

    cin >> q;
    while (q--) {
        int k, d;
        cin >> k;
        #ifdef tmd
        vector<int> id;
        REP1 (i, n) {
            id.emplace_back(i);
        }
        random_shuffle(id.begin(), id.end());
        #endif
        REP (ts, k) {
            #ifdef tmd
            d = id[ts];
            #else
            cin >> d;
            #endif
            imp_vec.emplace_back(d);
            is_imp[d] = true;
        }
        debug("ipt");
        build_virtual();
        debug("vired");

        sum = mx = 0;
        mn = MOD;
        solve(1);

        cout << sum << " " << mn << " " << mx << endl;

        for (auto v : imp_vec) {
            is_imp[v] = false;
        }

        imp_vec.clear();
    }

}
