#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;
ll fac[1000005];

ll mpow(ll base,ll ex) {
    if (ex == 1) {
        return base;
    }
    ll tmp = mpow(base,ex/2);
    tmp = tmp * tmp % MOD;
    return (ex&1) ? tmp * base % MOD : tmp;
}

ll inv(ll val) {
    return mpow(val,MOD-2);
}

int main () {
    fac[0] = 1;
    for (ll i=1;i<1000005;i++) {
        fac[i] = fac[i-1] * i % MOD;
    }

    ll n;
    cin >> n;

    ll ans = fac[n];
    for (ll i=1;i<n;i++) {
        ll tmp = fac[n] * inv(fac[n-i]) % MOD;
        tmp = tmp * (fac[n-i] - 1) % MOD;
        ans = (ans + tmp) % MOD;
    }

    cout << ans << endl;
}