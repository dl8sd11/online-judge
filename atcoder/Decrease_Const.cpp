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

ll k, a[100];
/*********************GoodLuck***********************/
int main () {
    IOS();

    while (cin >> k) {
        ll n = 50;
        cout << n << endl;
        REP (i, n) {
            if (i < k % n) {
                a[i] = k/n + n - 1 + n - k % n + 1;
                cout << a[i] << " \n"[i==n-1];
            } else {
                a[i] = k/n + n - 1 - (k % n);
                cout << a[i] << " \n"[i==n-1];
            }
        }


#ifdef tmd
        ll ans= 0;
        while (true) {
            ll mx = 0;
            REP (i, n) {
                if (a[i] >= a[mx]) {
                    mx = i;
                }
            }
            if (a[mx] < n) {
                break;
            }
            ans++;
            a[mx] -= n;
            REP (i, n) {
                if (i != mx) {
                    a[i] += 1;
                }
            }

        }
        cout << ans << endl;
#endif

    }
    return 0;
}
