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
const ll MOD = 998244353;

ll check_square (ll val) {
    ll l = 0, r = 1424213562;
    while (l < r - 1) {
        ll mid = (l + r) >> 1;
        if (mid * mid > val) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return l * l == val ? l : -1;
}

ll check_cube (ll val) {
    ll l = 0, r = 1260000;
    while (l < r - 1) {
        ll mid = (l + r) >> 1;
        if (mid * mid * mid > val) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return l * l * l == val ? l : -1;
}
map<ll, int> p, pq;
int n;
ll a[502];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        cin >> a[i];
    }

    REP (i, n) {
        ll sq1 = check_square(a[i]);
        ll cu = check_cube(a[i]);
        if (cu != -1) {
            p[cu] += 3;
        } else if (sq1 != -1) {
            ll sq2 = check_square(sq1);
            if (sq2 != -1) {
                p[sq2] += 4;
            } else {
                p[sq1] += 2;
            }
        } else {
            bool flag = true;
            REP (j, n) {
                ll g = __gcd(a[i], a[j]);
                if (g > 1 && g < a[i]) {
                    p[g]++;
                    p[a[i] / g]++;
                    flag = false;
                    break;
                }
            }
            if (flag) {
                pq[a[i]]++;
            }
        }
    }

    ll ans = 1;
    for (auto pa : p) {
        ans = ans * (pa.second + 1) % MOD;
    }
    for (auto pa : pq) {
        ans = ans * (pa.second + 1) * (pa.second + 1) % MOD;
    }

    cout << ans << endl;

    return 0;
}
