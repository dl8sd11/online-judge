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

const int MAXN = 1003;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;

int n, m;
int keys[MAXN], a[MAXN], dp[2][1<<12];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP1 (i, m) {
        int k;
        cin >> a[i] >> k;
        REP (j, k) {
            int d;
            cin >> d;
            keys[i] |= (1<<(d-1));
        }
    }

    memset(dp, 0x3f3f3f3f, sizeof(dp));

    dp[0][0] = dp[1][0] = 0;

    REP1 (i, m) {
        REP (j, (1<<n)) {
            dp[i&1][j] = dp[i&1^1][j];
            if ((keys[i] & j) == keys[i]) {
                dp[i&1][j] = min(dp[i&1^1][j^keys[i]] + a[i], dp[i&1][j]);
                for (int st=keys[i]; st>0; st=(st-1)&keys[i]) {
                    dp[i&1][j] = min(dp[i&1^1][(j^keys[i])|st] + a[i], dp[i&1][j]);
                }
            }
        }
    }

    cout << (dp[m&1][(1<<n)-1] == 0x3f3f3f3f ? -1 : dp[m&1][(1<<n)-1]) << endl;
    return 0;
}
