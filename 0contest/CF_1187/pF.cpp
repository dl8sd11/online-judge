#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;
typedef long long ll;

const ll MOD = 1000000007;
const ll MAXN = 200005;

ll n, l[MAXN], r[MAXN], exi[MAXN], pre[MAXN];
ll sxi, sxx;

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

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i=0;i<n;i++) {
        cin >> l[i];
    }
    for (int i=0;i<n;i++) {
        cin >> r[i];
    }
    for (int i=1;i<n;i++) {
        ll inter = max(0LL, min(r[i-1],r[i])-max(l[i-1],l[i])+1);
        exi[i] = nor(1 - inter * mpow((r[i]-l[i]+1)*(r[i-1]-l[i-1]+1)%MOD, MOD-2));
        pre[i] = (pre[i-1] + exi[i]) % MOD;
        sxi = (sxi + exi[i]) % MOD;
    }

    for (int i=0; i<n-2;i++) {
        sxx = nor(sxx + (pre[n-1] - pre[i+1])*exi[i]);
    }

    for (int i=2; i<n;i++) {
        ll inter = max(0LL, min({r[i],r[i-1],r[i-2]})-max({l[i],l[i-1],l[i-2]})+1);
        ll L = max(0LL, min(r[i-2],r[i-1])-max(l[i-2],l[i-1])+1)*(r[i]-l[i]+1)%MOD;
        ll R = max(0LL, min(r[i-1],r[i])-max(l[i-1],l[i])+1)*(r[i-2]-l[i-2]+1)%MOD;
        ll sum = (r[i]-l[i]+1)*(r[i-1]-l[i-1]+1)%MOD*(r[i-2]-l[i-2]+1)%MOD;
        sxx = nor(sxx+1-(L + R - inter)%MOD*mpow(sum,MOD-2));
    }
    
    cout << nor(1+3*sxi+2*sxx) << endl;
}