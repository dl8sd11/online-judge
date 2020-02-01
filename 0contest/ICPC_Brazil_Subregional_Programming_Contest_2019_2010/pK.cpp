#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 500005;
const ll MOD = 1000000007;

int n;
ll dp[MAXN], ans[MAXN];
/****GOOD_LUCK****/
int main () {
    IOS();

    cin >> n;

    dp[0] = ans[0] = 1;
    dp[1] = ans[1] = 2;
    for (int i=2; i<=n; i++) {
        dp[i] = dp[i-1] * 2 % MOD;
        ans[i] = 2*(dp[i-1]+ans[i-2]*2+ans[i-1]) % MOD;
    }

    cout << ans[n] << endl;
    return 0;
}
