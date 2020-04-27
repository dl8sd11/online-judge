#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int d, m;
        cin >> d >> m;

        ll dp[32] = {};
        dp[0] = 1;

        int lg = __lg(d) + 1;
        ll ans = 0;
        for (int i=1; i<=lg; i++) {
            int mul;
            if (i == lg) {
                mul = d - (1<<lg-1) + 1;
            } else {
                mul = 1<<(i-1);
            }

            for (int j=0; j<i; j++) {
                dp[i] += mul * dp[j];
                dp[i] %= m;
            }

            ans = (ans + dp[i]) % m;
        }

        cout << ans << endl;

    }
}
