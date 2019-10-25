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
const int MOD = 1000000007;

int n, m, dp[MAXN];

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    dp[0] = dp[1] = 1;
    for (int i=2; i<=max(n, m); i++) {
        dp[i] = (dp[i-1] + dp[i-2]) % MOD;
    }

    int cur = (dp[n] + dp[m] - 1) % MOD;
    cur = (cur + MOD) % MOD * 2 % MOD;

    cout << cur << endl;

}
