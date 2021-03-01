#include <bits/stdc++.h>
using namespace std;

int a[10];
int dp[10][10];
int f(int l, int r) {
    if (dp[l][r] != -1) return dp[l][r];
    if (l == r - 1) return 0;
    dp[l][r] = 0x3f3f3f3f;
    int sm = 0;
    for (int i=l;i<r; i++) sm += a[i];
    for (int m=l+1; m<r; m++) {
        dp[l][r] = min(dp[l][r], f(l,m) + f(m,r));
    }
    dp[l][r] += sm;
    return dp[l][r];
}
int main () {
    memset(dp, -1, sizeof(dp));
    int n;
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> a[i];
    }
    cout << f(0, n) << endl;

}
