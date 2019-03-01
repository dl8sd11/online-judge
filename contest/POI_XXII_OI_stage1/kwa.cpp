#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define SZ(i) ll(i.size())
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
#define MEM(i,n) memset(i,n,sizeof(i))
#ifdef tmd
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
#define IOS()
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#endif
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll MAXN = 1000003;
ll n,dp[MAXN];
ll pre[MAXN];
int main () {
    IOS();
    cin >> n;
    REP1 (i,n) {
        pre[i] += pre[i-1] + i*i;
    }
    MEM(dp,INF);
    dp[0] = 0;
    REP1 (i,n) {
        for (ll j=1;j*j<=i;j++) {
            if (dp[i-j*j] < j) {
                dp[i] = min(dp[i],j);
            }
        }
    }
    if (dp[n] == INF) {
        cout << "- ";
    }else {
        cout << dp[n] << " ";
    }
    ll ans = 0;
    for (ll i=1;i<=n;i++) {
        if (dp[i] == INF || pre[dp[i]-1] > i) {
            ans++;
        }
    }
    cout << ans << endl;
}