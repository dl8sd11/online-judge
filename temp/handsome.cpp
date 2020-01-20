#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;

const int MAXN = 2001;
int n, a;
ll dp[MAXN+1][MAXN+1];
ll pre[MAXN];
ll solve (int l, int r) {
    if (dp[l][r] != -1) {
        return dp[l][r];
    }
    dp[l][r] = 0;
    if (l == r) {
        return dp[l][r];
    }

    ll sum = pre[r-1] - pre[l-1];
    return dp[l][r] = max(sum-solve(l,r-1),sum-solve(l+1, r));
}
int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    memset(dp, -1, sizeof(dp));

    cin >> n;

    ll sum = 0;
    for (int i=1;i<=n;++i) {
        cin >> a;
        sum += a;
        pre[i] = sum;
    }

    cout << solve(1,n+1) << endl;
}