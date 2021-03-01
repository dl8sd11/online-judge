#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 998244353;

vector<ll> get_factor (ll n) {
    vector<ll> factors;
    for (ll i=1; i*i<=n; i++) {
        if (n % i == 0) {
            factors.emplace_back(i);
            factors.emplace_back(n / i);
        }
    }
    if (factors.back() == factors[factors.size()-1]) factors.pop_back();
    return factors;
}

int main () {
    int n;
    ll  k;
    cin >> n >> k;
    
    
}
