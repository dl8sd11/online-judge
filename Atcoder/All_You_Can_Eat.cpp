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

const int MAXN = 3003;
const ll MOD = 1000000007;

int n, t, pre[MAXN], dp[MAXN][MAXN];
vector<pair<int,int> > food;
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n >> t;

    food.emplace_back(-1, 0);
    REP1 (i, n) {
        int a, b;
        cin >> a >> b;
        food.emplace_back(a, b);
    }
    sort(food.begin(), food.end());


    for (int i=n; i>=1; i--) {
        pre[i] = max(pre[i+1], food[i].second);
    }

    int ans = 0;
    REP1 (i, n) {
        for (int k=0; k<t; k++) {
            dp[i][k] = dp[i-1][k];
            if (k >= food[i].first) {
                dp[i][k] = max(dp[i-1][k-food[i].first]+food[i].second, dp[i][k]);
            }
            ans = max(ans, dp[i][k] + pre[i+1]);
        }
    }

    cout << ans << endl;
}
