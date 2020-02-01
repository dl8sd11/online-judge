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

const int MAXN = 10004;
const ll MOD = 1000000007;

int t, n, m, scc[MAXN], scnt, sz[MAXN];
bool vis[MAXN];
vector<int> edge[MAXN], G[MAXN], rG[MAXN], topo;

void dfs1 (int nd) {
    vis[nd] = true;
    for (auto v : G[nd]) {
        if (!vis[v]) {
            dfs1(v);
        }
    }
    topo.emplace_back(nd);
}

void dfs2 (int nd) {
    vis[nd] = false;
    scc[nd] = scnt;
    sz[scnt]++;
    for (auto v : rG[nd]) {
        if (vis[v]) {
            dfs2(v);
        }
    }
}

int dp[MAXN];

void dfs3 (int nd) {
    if (dp[nd]) {
        return;
    }

    int ret = 0;
    for (auto v : edge[nd]) {
        dfs3(v);
        ret = max(ret, dp[v]);
    }

    dp[nd] =  ret + sz[nd];
    return;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> n >> m;
        REP (e, m) {
            int f, w;
            cin >> f >> w;
            G[f].emplace_back(w);
            rG[w].emplace_back(f);
        }
        topo.clear();
        scnt = 0;
        REP1 (i, n) {
            if (!vis[i]) {
                dfs1(i);
            }
        }

        for (int i=n-1; i>=0; i--) {
            int x = topo[i];
            if (vis[x]) {
                sz[scnt] = 0;
                dfs2(x);
                scnt++;
            }
        }

        int ans = 0;
        memset(dp, 0, sizeof(dp));

        REP1 (i, n) {
            for (auto x : G[i]) {
                if (scc[i] != scc[x]) {
                    edge[scc[i]].emplace_back(scc[x]);
                }
            }
        }

        REP (i, scnt) {
            dfs3(i);
            ans = max(dp[i], ans);
        }

        cout << ans << endl;

        REP1 (i, n) {
            G[i].clear();
            rG[i].clear();
            edge[i-1].clear();
        }
    }

}
