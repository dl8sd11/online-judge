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

const int MAXN = 500005;
const ll MOD = 1000000007;

ll n, x, y;
struct Critical {
    ll mn, mx;
    Critical () {
        mn = 0x3f3f3f3f, mx = -(0x3f3f3f3f);
    }

    void upd (ll v) {
        mn = min(mn, v);
        mx = max(mx, v);
    }
} ctp[4], sta[2]; // r, l, u, d

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;

    REP (i, n) {
        cin >> x >> y;
        x *= 2, y *= 2;
        char d;
        cin >> d;
        if (d == 'R') {
            ctp[0].upd(x);
            sta[1].upd(y);
        } else if (d == 'L') {
            ctp[1].upd(x);
            sta[1].upd(y);
        } else if (d == 'U') {
            sta[0].upd(x);
            ctp[2].upd(y);
        } else {
            sta[0].upd(x);
            ctp[3].upd(y);
        }
    }

    ll ans = 0x3f3f3f3f3f3f3f3f;
    REP (i, 800000050) {
        ll mnx = min({sta[0].mn, ctp[0].mn+i, ctp[1].mn-i});
        ll mxx = max({sta[0].mx, ctp[0].mx+i, ctp[1].mx-i});
        ll mny = min({sta[1].mn, ctp[2].mn+i, ctp[3].mn-i});
        ll mxy = max({sta[1].mx, ctp[2].mx+i, ctp[3].mx-i});

        ans = min(ans, (mxx-mnx)*(mxy-mny));
    }
    if (ans % 4 == 0) {
        cout << ans/4 << endl;
    } else {
        if (ans % 4 == 1 || ans % 4 == 3) {
            cout << ans/4 << "." << ans%4*25 << endl;
        } else {
            cout << ans/4 << ".5" << endl;
        }
    }

}
