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

const int MAXN = 51;
const ll MOD = 1000000007;

int n, m, bridge_cnt;
vector<int> edge[MAXN];

int dfn[MAXN], low[MAXN], tme;
bool vis[MAXN];

void dfs (int nd, int par) {
    dfn[nd] = low[nd] = ++tme;
    vis[nd] = true;
    debug(nd);

    for (auto v : edge[nd]) {
        if (v != par) {
            if (!vis[v]) {
                dfs(v, nd);
                low[nd] = min(low[nd], low[v]);
                if (low[v] >= dfn[v]) {
                    bridge_cnt++;
                }
            } else if (dfn[v] < dfn[nd]){
                debug(v, nd);
                low[nd] = min(low[nd], dfn[v]);
            }
        }
    }

    debug(low[nd], dfn[nd], nd);
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, m) {
        int u, v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    dfs(1, 1);

    cout << bridge_cnt << endl;
}
