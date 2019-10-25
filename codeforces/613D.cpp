#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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

const int MAXN = 100005;
const ll MOD = 1000000007;
const int MAXLG = __lg(MAXN) + 3;

int n, q, anc[MAXLG][MAXN], dep[MAXN], dfn[MAXN], ts;
vector<int> edge[MAXN];

void build_anc (int nd, int par) {
    anc[0][nd] = par;
    dep[nd] = dep[par] + 1;
    dfn[nd] = ts++;
    for (auto v : edge[nd]) {
        if (v != par) {
            build_anc(v, nd);
        }
    }
}

void build_lca () {
    REP1 (i, MAXLG-1) {
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

    return anc[0][u];
}

vector<int> imp, virt_v, virt_e[MAXN];
int dp[MAXN][2];
bool is_imp[MAXN];

void build_virtual () {
    sort(imp.begin(), imp.end(), [](int a, int b) {
        return dfn[a] < dfn[b];
    });
    vector<int> stk = {1};
    for (auto cv : imp) {
        if (cv != 1) {
            int hd = lca(cv, stk.back());
            if (hd == stk.back()) {
                stk.emplace_back(cv);
            } else {
                while (stk.size() >= 2 && dep[stk[stk.size() - 2]] >= dep[hd]) {
                    int sz = SZ(stk);
                    virt_e[stk[sz-1]].emplace_back(stk[sz-2]);
                    virt_e[stk[sz-2]].emplace_back(stk[sz-1]);
                    virt_v.emplace_back(stk.back());
                    stk.pop_back();
                }

                if (stk.back() != hd) {

                    virt_e[stk.back()].emplace_back(hd);
                    virt_e[hd].emplace_back(stk.back());
                    virt_v.emplace_back(stk.back());
                    stk.pop_back();
                    stk.emplace_back(hd);
                }

                stk.emplace_back(cv);
            }
        }
    }
    while (stk.size()) {
        int sz = SZ(stk);
        if (sz >= 2) {
            virt_e[stk[sz-1]].emplace_back(stk[sz-2]);
            virt_e[stk[sz-2]].emplace_back(stk[sz-1]);
        }
        virt_v.emplace_back(stk.back());
        stk.pop_back();
    }
}

void clear_virtual () {
    for (auto v : virt_v) {
        virt_e[v].clear();
        is_imp[v] = false;
    }
    virt_v.clear();
}

void print_virtual_graph () {
    for (auto v : virt_v) {
        debug(v);
        for (auto ev : virt_e[v]) {
            cout << ev << " ";
        }
        cout << endl;
    }
}

const int INF = 0x3f3f3f3f;
void solve (int nd, int par) {
    for (auto v : virt_e[nd]) {
        if (v != par) {
            solve(v, nd);
        }
    }

    if (is_imp[nd]) {
        dp[nd][0] = 0;
        dp[nd][1] = INF;
        for (auto v : virt_e[nd]) {
            if (v != par) {
                if (is_imp[v] && dep[v] == dep[nd] + 1) {
                    dp[nd][0] = INF;
                } else {
                    if (dp[nd][0] < INF) {
                        dp[nd][0] += min(dp[v][0] + 1, dp[v][1]);
                    }
                }
            }
        }
    } else {
        ll dp1 = 0;
        dp[nd][0] = 0;
        dp[nd][1] = 1;
        for (auto v : virt_e[nd]) {
            if (v != par) {
                dp1 += dp[v][1];
                dp[nd][1] += min(dp[v][0], dp[v][1]);
                dp[nd][0] = min(dp[nd][0], dp[v][0] - dp[v][1]);
            }
        }
        int dpi = dp1 > INF ? INF : int(dp1);
        dp[nd][1] = min(dp[nd][1], dpi);
        ll nw = dp1 + dp[nd][0];
        dp[nd][0] = nw > INF ? INF : int(nw);
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    build_anc(1, 1);
    build_lca();

    cin >> q;
    while (q--) {
        int k;
        cin >> k;
        imp.clear();
        REP (i, k) {
            int d;
            cin >> d;
            imp.emplace_back(d);
            is_imp[d] = true;
        }

        build_virtual();

        #ifdef tmdd
        print_virtual_graph();
        #endif

        solve(1, 1); // assert 1 is root
        clear_virtual();

        dp[1][0] = min(dp[1][0], dp[1][1]);
        cout << (dp[1][0] == INF ? -1 : dp[1][0]) << endl;

    }
    return 0;
}
