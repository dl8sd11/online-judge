#include <iostream>
using namespace std;
typedef long long ll;

const ll MOD = 1000000007;

ll mpow(ll base,ll ep) {
    ep = ep % (MOD - 1);
    ll ret = 1;
    while (ep > 0) {
        if (ep & 1) {
            ret = ret * base % MOD;
        }
        base = base * base % MOD;
        ep >>= 1;
    }
    return ret;
}

ll nor(ll x) {
    return (x%MOD + MOD) % MOD;
}

ll n, l[200005], r[200005];
ll sxi, sxi2;

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << 53 * mpow(8, MOD-2) % MOD << endl;
    cin >> n;
    for (int i=0;i<n;i++) {
        cin >> l[i];
    }
    for (int i=0;i<n;i++) {
        cin >> r[i];
    }
    for (int i=1;i<n;i++) {
        ll inter = max(0LL, min(r[i-1],r[i])-max(l[i-1],l[i])+1);
        ll cur = nor(1 - inter * mpow((r[i]-l[i]+1)*(r[i-1]-l[i-1]+1)%MOD, MOD-2));
        sxi = (sxi + cur) % MOD;
        sxi2 = (sxi2 + cur*cur) % MOD;
    }

    cout << sxi << " " << mpow(2, MOD-2) << endl;
    cout << sxi2 << " " << mpow(8, MOD-2) << endl;
    cout << nor(1+3*sxi-sxi2+sxi*sxi%MOD) << endl;
}