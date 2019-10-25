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

ll n, p, w, d;
void check (ll x, ll y, ll z) {
    if (x >= 0 && y >= 0 && z >= 0) {
        if (x + y + z == n) {
            if (x*w + y*d == p) {
                cout << x << " " << y << " " << z << endl;
                exit(0);
            }
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> p >> w >> d;
    ll wc = p / w;
    for (ll i=0; i<=wc && i<100005; i++) {
        ll dc = (p - (wc-i)*w) / d;
        ll lc = n - (wc-i) - dc;
        check(wc-i, dc, lc);
    }

    cout << -1 << endl;
    return 0;
}
