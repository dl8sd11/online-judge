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

const int MAXN = 202;
const ll MOD = 998244353;

typedef complex<ll> point;

ll cross (const point &p1, const point &p2) {
    return (conj(p1)*p2).imag();
}

ll mpow (ll bs, ll ep) {
    ll ret = 1;
    while (ep) {
        if (ep & 1) {
            ret = ret * bs % MOD;
        }
        ep >>= 1;
        bs = bs * bs % MOD;
    }
    return ret;
}

int n;
ll ans;
point p[MAXN];

ll md (ll x) {
    return (x % MOD + MOD) % MOD;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    ans = mpow(2, n) - 1 - n;
    REP (i, n) {
        int x, y;
        cin >> x >> y;
        p[i] = {x, y};
    }

    REP (i, n) {
        REP (j, i) {
            ll c = 0;
            REP (k, n) {
                if (cross(p[i]-p[j], p[k]-p[j]) == 0) {
                    c++;
                }
            }
            ans -= md(mpow(2, c) - 1 - c) * mpow(c*(c-1)/2, MOD-2) % MOD;
            ans = md(ans);
        }
    }

    cout << ans << endl;

    return 0;
}
