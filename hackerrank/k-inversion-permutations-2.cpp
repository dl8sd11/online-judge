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
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;

int dp[102][102];
/*********************GoodLuck***********************/
int main () {
    IOS();

    int n, k;
    cin >> n >> k;

    dp[0][0] = 1;
    REP1 (i, n) {
        REP (j, k+1) {
            for (int l=0; l<i && l<=j; l++) {
                dp[i][j] += dp[i-1][j-l];
                dp[i][j] %= MOD;
            }
        }
    }

    cout << dp[n][k] << endl;

    return 0;
}
