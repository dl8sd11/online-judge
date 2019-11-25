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

ll m;

array<ll,2> water (ll h, ll a, ll x, ll y) {
    array<ll,2> ret = {-1, 0};

    REP1 (i, m*3) {
        h = (x*h+y) % m;

        if (h == a) {
            if (ret[0] == -1) {
                ret[0] = i;
            } else {
                ret[1] = i - ret[0];
                break;
            }
        }
    }
    return ret;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> m;
    vector<array<ll,2> > tim(2);
    REP (i, 2) {
        ll h, a, x, y;
        cin >> h >> a >> x >> y;
        tim[i] = water(h, a, x, y);
    }
    debug(tim[0][0], tim[0][1]);
    debug(tim[1][0], tim[1][1]);
    if (tim[0][0] < 0 || tim[1][0] < 0) {
        cout << -1 << endl;
        return 0;
    }

    ll ans = -1;
    REP (i, m) {
        ll cur = tim[0][1]*i + tim[0][0];
        ll x = tim[1][1] ? (cur - tim[1][0]) / tim[1][1] : 0;
        if (x >= 0 && tim[1][1]*x + tim[1][0] == cur) {
            ans = cur;
            break;
        }
    }

    cout << ans << endl;
}
