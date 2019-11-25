#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmdd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 102;
const ll MOD = 1000000007;

int n, ap_cnt, dfn[MAXN], low[MAXN], tme;
vector<int> edge[MAXN];
bool vis[MAXN];

void dfs (int nd, int par) {
    dfn[nd] = low[nd] = ++tme;
    vis[nd] = true;
    debug(nd, par);
    int child = 0;
    bool is_ap = false;
    for (auto v : edge[nd]) {
        if (vis[v]) {
            low[nd] = min(low[nd], dfn[v]);
        } else {
            dfs(v, nd);
            low[nd] = min(low[nd], low[v]);
            child++;

            if (low[v] >= dfn[nd]) {
                is_ap = true;
            }
        }
    }
    debug(low[nd], dfn[nd], nd);

    if (nd == par) {
        ap_cnt += child > 1;
    } else {
        ap_cnt += is_ap;
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    while (cin >> n && n != 0) {
        cin.ignore();
        string line;
        while (getline(cin, line)) {
            stringstream ss(line);
            int u, v;
            ss >> u;
            if (u == 0) {
                break;
            }
            while (ss >> v) {
                debug(u, v);
                edge[u].emplace_back(v);
                edge[v].emplace_back(u);
            }
        }

        ap_cnt = tme = 0;
        memset(vis, 0, sizeof(vis));
        REP1 (i, n) {
            if (!vis[i]) {
                dfs(i, i);
            }
        }

        cout << ap_cnt << endl;
        REP1 (i, n) {
            edge[i].clear();
        }
    }
}
