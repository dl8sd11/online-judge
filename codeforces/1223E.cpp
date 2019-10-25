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

int q, n, k;
ll dp[MAXN][2];
vector<pair<int,int> > edge[MAXN];

void dfs (int nd, int par) {
    dp[nd][0] = dp[nd][1] = 0;

    ll sum = 0;
    vector<ll> dlt;
    for (auto v : edge[nd]) {
        if (v.first != par) {
            dfs(v.first, nd);
            sum += dp[v.first][0];
            dlt.emplace_back(max(0LL, dp[v.first][1]+v.second-dp[v.first][0]));
        }
    }
    ll x = 0;
    sort(dlt.rbegin(), dlt.rend());
    REP (i, min(SZ(dlt), k-1)) {
        x += dlt[i];
    }
    dp[nd][1] = sum + x;
    dp[nd][0] = sum + x + (k<=SZ(dlt) ? dlt[k-1] : 0);
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> q;
    while (q--) {
        cin >> n >> k;
        REP (i, n-1) {
            int u, v, w;
            cin >> u >> v >> w;
            edge[u].emplace_back(v, w);
            edge[v].emplace_back(u, w);
        }


        dfs(1, 1);

        debug(dp[4][0], dp[4][1]);
        debug(dp[3][0], dp[3][1]);
        debug(dp[2][0], dp[2][1]);
        debug(dp[1][0], dp[1][1]);

        cout << max(dp[1][0], dp[1][1]) << endl;
        REP1 (i, n) {
            edge[i].clear();
        }
    }

}
