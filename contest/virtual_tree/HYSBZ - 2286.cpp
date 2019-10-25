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

const int MAXN = 250005;
const ll MOD = 1000000007;
const int MAXLG = 21;

int n, m, anc[MAXLG][MAXN], mn[MAXLG][MAXN], dep[MAXN], in[MAXN], tim;
ll dp[MAXN];
vector<pii> edg[MAXN];

void dfs_anc (int nd, int par) {
    in[nd] = tim++;
    anc[0][nd] = par;
    dep[nd] = dep[par] + 1;
    for (pii v : edg[nd]) {
        if (v.first != par) {
            dfs_anc(v.first, nd);
            mn[0][v.first] = v.second;
        }
    }
}

void build_anc () {
    REP1 (i, MAXLG - 1) {
        REP1 (j, n) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
            mn[i][j] = min(mn[i-1][j], mn[i-1][anc[i-1][j]]);
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
        if (anc[i][u] != anc[i][v]) {
            u = anc[i][u];
            v = anc[i][v];
        }
    }

    return anc[0][v];
}

int pth (int nd, int pp) {
    int ret = 0x3f3f3f3f;
    for (int i=MAXLG-1; i>=0; i--) {
        if (dep[anc[i][nd]] > dep[pp]) {
            ret = min(ret, mn[i][nd]);
            nd = anc[i][nd];
        }
    }
    return min(ret, mn[0][nd]);
}

vector<int> h;
vector<pii> vtree[MAXN];
vector<int> virtual_vertex;
bool imp[MAXN];

void add_vedg (int f, int t) {
    vtree[f].emplace_back(t, pth(t, f));
    debug(f, t, pth(t, f));
}

void clear_virtual () {
    for (int v : virtual_vertex) {
        vtree[v].clear();
        imp[v] = false;
    }
    virtual_vertex.clear();
    h.clear();
}

void build_virtual () {
    sort(h.begin(), h.end(), [](int a, int b) {
        return in[a] < in[b];
    });

    vector<int> stk = {1};
    for (int v : h) {
        int lret = lca(v, stk.back());
        debug(v, stk.back(), lret);
        if (lret == stk.back()) {
            stk.emplace_back(v);
        } else {
            while (dep[stk[SZ(stk)-2]] >= dep[lret]) {
                int lst = stk.back();
                stk.pop_back();
                virtual_vertex.emplace_back(lst);
                add_vedg(stk.back(), lst);
            }
            debug(stk.back(), lret);
            if (stk.back() != lret) {
                add_vedg(lret, stk.back());
                virtual_vertex.emplace_back(stk.back());
                stk.pop_back();
                stk.emplace_back(lret);
            }
            stk.emplace_back(v);
        }
    }

    while (stk.size()) {
        int lst = stk.back();
        stk.pop_back();
        virtual_vertex.emplace_back(lst);
        if (!stk.empty()) {
            add_vedg(stk.back(), lst);
        }
    }
}

void solve (int nd) {
    dp[nd] = 0;
    for (pii e : vtree[nd]) {
        solve(e.first);
        if (imp[e.first]) {
            dp[nd] += e.second;
        } else {
            dp[nd] += min(dp[e.first], ll(e.second));
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n-1) {
        int u, v, c;
        cin >> u >> v >> c;
        edg[u].emplace_back(v, c);
        edg[v].emplace_back(u, c);
    }

    dfs_anc(1, 1);
    build_anc();

    cin >> m;

    while (m--) {
        int k, d;
        cin >> k;

        REP (i, k) {
            cin >> d;
            h.emplace_back(d);
            imp[d] = true;
        }

        build_virtual();
        solve(1);


        clear_virtual();

        cout << dp[1] << endl;
    }
}
