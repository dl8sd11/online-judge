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

const int MAXN = 200005;
const ll MOD = 1000000007;

int n, a[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    ll suf = 0;
    REP (i, n) {
        cin >> a[i];
        suf += a[i];
    }

    ll pre = 0, ans = 0x3f3f3f3f3f3f3f3f;
    REP (i, n-1) {
        pre += a[i];
        suf -= a[i];
        ans = min(ans, abs(pre - suf));
    }

    cout << ans << endl;
    return 0;
}
