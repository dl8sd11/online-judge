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

ll n, a[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;

    REP (i, n) {
        cin >> a[i];
    }
    sort(a, a+n);

    ll ans = 0;

    vector<ll> gp = {a[n-1]};
    for (int i=n-2; i>=0; i--) {
        ll stp = (gp.back() - a[i]) / (n + 1);
        debug(stp, gp.back(), a[i]);
        for (auto &el : gp) {
            el -= (n - SZ(gp) + 1) * stp;
        }
        ans += SZ(gp) * stp;
        for (int j=0; j<=i; j++) {
            a[j] += stp * SZ(gp);
        }
        gp.emplace_back(a[i]);
    }

    while (true) {
        sort(gp.begin(), gp.end());
        if (gp[n-1] < n) {
            break;
        } else if (gp[n-1] - gp[0] < n) {
            break;
        }
        gp[n-1] -= n;
        for (int i=0; i<n-1; i++) {
            gp[i]++;
        }
        ans++;
    }


    ll dl = max(0LL, gp[0] - (n-1));
    REP (i, n) {
        gp[i] -= dl;
        ans += dl;
    }

    while (true) {
        sort(gp.begin(), gp.end());
        if (gp[n-1] < n) {
            break;
        }
        gp[n-1] -= n;
        for (int i=0; i<n-1; i++) {
            gp[i]++;
        }
        ans++;
    }


    cout << ans<< endl;
    return 0;
}
