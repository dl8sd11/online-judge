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

const int MAXN = 5003;
const ll MOD = 1000000007;

ll dp[MAXN*MAXN], n, p[3], q[3];

void build () {
    memset(dp, 0, sizeof(dp));
    REP (i, 3) {
        REP (j, MAXN*MAXN) {
            if (j >= p[i]) {
                dp[j] = max(dp[j-p[i]]+(q[i]-p[i]), dp[j]);
            }
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n;
    REP (j, 3) {
        cin >> p[j];
    }
    REP (j, 3) {
        cin >> q[j];
    }

    build();
    ll t = n + dp[n];
    swap(p, q);
    build();
    cout << t + dp[t] << endl;


}
