#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;
inline ll __lcm(ll a,ll b) {
    return a * b / __gcd(a,b);
}
inline ll lcd(ll a,ll b,ll c) {
    return __lcm(__gcd(a,b),c);
}
inline ll gcm(ll a,ll b,ll c) {
    return __gcd(__lcm(a,b),c);
}
int main () {
    ll n,sum = 1;
    cin >> n;
    for (ll i=1;i<=n;i++) {
        for (ll j=1;j<=n;j++) {
            for (ll k=1;k<=n;k++) {
                sum = sum * lcd(i,j,k) % MOD * gcm(i,j,k) % MOD;
            }
        }
    }

    cout << sum << endl;
}