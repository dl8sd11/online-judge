#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)

const int MAXN = 200005, MOD = 998244353;

int main () {
    IOS();

    int n;
    cin >> n;
    vector<long long> a(n), b(n), c(n);
    

    for (int i=0;i<n;i++) {
        cin >> a[i];
        a[i] = a[i] * (i + 1) * (n - i);
    }
    for (int i=0;i<n;i++) {
        cin >> b[i];
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    long long ans = 0;
    for (int i=0;i<n;i++) {
        ans = (ans + a[i] % MOD * b[n-i-1]) % MOD;
    }
    cout << ans << endl;
}
