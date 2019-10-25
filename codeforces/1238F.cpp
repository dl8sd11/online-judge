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

const int MAXN = 500005;
const ll MOD = 1000000007;

int q, n, dp[MAXN], ans, root;
vector<int> edg[MAXN];


void dfs (int nd, int par) {
    dp[nd] = SZ(edg[nd]) + (nd == root);

    pair<int,int> bst;
    for (auto v : edg[nd]) {
        if (v != par) {
            dfs(v, nd);
            dp[nd] = max(dp[nd], dp[v] + SZ(edg[nd]) - (root!=nd));
            if (dp[v] > bst.first) {
                bst.second = bst.first;
                bst.first = dp[v];
            } else if (dp[v] > bst.second) {
                bst.second = dp[v];
            }
        }
    }

    ans = max(ans, dp[nd] + (root != nd));
    ans = max(ans, bst.first + bst.second + SZ(edg[nd]) - 1);
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    root = 1;
    cin >> q;

    while (q--) {
        cin >> n;
        REP (i, n-1) {
            int u, v;
            cin >> u >> v;
            edg[u].emplace_back(v);
            edg[v].emplace_back(u);
        }

        ans = 0;
        dfs(1, 1);

        cout << ans << endl;

        REP1 (i, n) {
            edg[i].clear();
        }
    }
}
