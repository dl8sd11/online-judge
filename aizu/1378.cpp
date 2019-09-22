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

const int MAXN = 1000006;
const ll MOD = 1000000007;

int l, k;
ll dp[102][102];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> l >> k;
    dp[0][0] = 1;
    ll ans = 0;
    REP1 (i, 100) {
        REP1 (j, l) {
            if (i & 1) {
                if (j >= k) {
                    dp[i][j] += dp[i-1][j-k];
                }
                dp[i][j] += dp[i-1][j-1];
                debug(i, j, dp[i][j]);
                ans += dp[i][j];
            } else {
                dp[i][j] += dp[i-1][j-1];
            }
        }
    }

    cout << ans << endl;
    return 0;
}
