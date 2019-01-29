#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN = 100003;
ll n,k;
ll a[MAXN],sum;
ll sg(ll x) {
    if (x == 0) {
        return 0;
    }
    if ((k&1) == 0) {
        if (x <= 2) {
            return x;
        } else {
            return 1 - (x&1);
        }
    } else {
        if (x ==1) {
            return 1;
        } else if (x == 2) {
            return 0;
        } else if (x == 3) {
            return 1;
        } else if (x == 4) {
            return 2;
        } else if (x&1) {
            return 0;
        } else {
            if (sg(x/2) == 1) {
                return 2;
            } else {
                return 1;
            }
        }
    }
}
int main () {
    cin >> n >> k;
    for (ll i=0;i<n;i++) {
        cin >> a[i];
        sum ^= sg(a[i]);
    }

    if (sum != 0) {
        cout << "Kevin" << endl;
    }  else {
        cout << "Nicky" << endl;
    }
}