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

const int MAXN = 102;
const ll MOD = 1000000007;

int n, dp[MAXN][11];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;

    int iNF = 0x3f3f3f3f;
    memset(dp, -iNF, sizeof(dp));
    dp[0][0] = 0;
    REP1 (i, n) {
        int d;
        cin >> d;
        REP (j, 10) {
            dp[i][j] = max(dp[i-1][j], dp[i-1][(j-d%10+10)%10] + d);
        }
    }

    int ans = 0;
    REP1 (i, 9) {
        debug(i, dp[n][i]);
        ans = max(ans, dp[n][i]);
    }

    cout << ans << endl;
    return 0;
}
