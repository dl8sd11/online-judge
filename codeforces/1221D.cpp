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
const ll INF = 0x3f3f3f3f3f3f3f3f;
int q, n, a[MAXN], b[MAXN];
ll dp[MAXN][3];

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> q;
    a[0] = -920;
    while (q--) {
        cin >> n;
        REP1 (i, n) {
            cin >> a[i] >> b[i];
        }

        REP1 (i, n) {
            REP (j, 3) {
                dp[i][j] = INF;
                REP (k, 3) {
                    if (a[i]+j != a[i-1]+k) {
                        dp[i][j] = min(dp[i][j], dp[i-1][k]+b[i]*j);
                    }
                }
            }
        }
        cout << min({dp[n][0], dp[n][1], dp[n][2]}) << endl;
    }
    return 0;
}
