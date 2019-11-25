#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#define eb emplace_back
#ifdef tmd
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#define IOS()
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#define endl '\n'
#endif

const int iNF = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 120005;
const int MOD = 100000007;

int n, dp[MAXN][2][3];
int main () {
    IOS();

    cin >> n;

    dp[0][0][0] = 1;
    REP1 (i, n) {
        REP (j, 2) {
            REP (k, 3) {
                dp[i][j][0] += dp[i-1][j][k] + (j?dp[i-1][j-1][k]:0);
                dp[i][j][0] %= MOD;
            }
            dp[i][j][1] = dp[i-1][j][0];
            dp[i][j][2] = dp[i-1][j][1];
        }
    }

    ll sum = 0;
    REP (j, 2) {
        REP (k, 3) {
            sum += dp[n][j][k];
        }
    }
    sum %= MOD;
    cout << sum << endl;

}
