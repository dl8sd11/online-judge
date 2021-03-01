#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define endl '\n'

int n, k, q;

const int MOD = 1000000007;
int add (int x, int y) {
    return x + y >= MOD ? x + y - MOD : x + y;
}

int mul (int x, int y) {
    return ll(x) * y % MOD;
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k >> q;
    vector<int> a(n);
    for (int i=0; i<n; i++) cin >> a[i];

    // dp[k][i] number of path start/end at i with length k
    vector<vector<int> > dp(k+1, vector<int>(n, 0)); 
    for (int i=0; i<n; i++) dp[0][i] = 1;
    for (int i=1; i<=k; i++) {
        dp[i][0] = dp[i-1][1];
        dp[i][n-1] = dp[i-1][n-2];
        for (int j=1; j<n-1; j++) {
            dp[i][j] = add(dp[i-1][j-1], dp[i-1][j+1]);
        }
    }

    int ans = 0;
    vector<int> sum(n, 0);
    for (int i=0; i<n; i++) {
        for (int j=0; j<=k; j++) {
            sum[i] = add(sum[i], mul(dp[j][i], dp[k-j][i]));
        }
        ans = add(ans, mul(sum[i], a[i]));
    }

    for (int i=0; i<q; i++) {
        int x, val;
        cin >> x >> val;
        x--;
        ans = add(ans, MOD - mul(sum[x], a[x]));
        a[x] = val;
        ans = add(ans, mul(sum[x], a[x]));

        cout << ans << endl;
    }

}
