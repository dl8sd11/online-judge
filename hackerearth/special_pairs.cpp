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

const int MAXN = 100005;
const ll MOD = 1000000007;
const int MAXC = 20;

// dp[mask]: num of a with subset of mask on
int t, n, a[MAXN], dp[1<<MAXC], cnt;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> n;
        cnt = 0;
        memset(dp, 0, sizeof(dp));

        REP (i, n) {
            cin >> a[i];
            ++dp[a[i]];
        }

        REP (i, MAXC) {
            REP (j, (1<<MAXC)) {
                if (j & (1<<i)) {
                    dp[j] = dp[j] + dp[j^(1<<i)];
                }
            }
        }

        ll ans = 0;
        REP (i, n) {
            ans += dp[(1<<MAXC)-1-a[i]];
        }

        cout << ans << endl;
    }

}
