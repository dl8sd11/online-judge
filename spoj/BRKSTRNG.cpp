#include <bits/stdc++.h>
using namespace std;

const int MAXM = 1003;

int n, m;
int pos[MAXM], p[MAXM], dp[MAXM][MAXM], tr[MAXM][MAXM];
int main () {
    memset(dp, 0x3f3f3f3f, sizeof(dp));
    ios_base::sync_with_stdio(0);cin.tie(0);
    while (cin >> n >> m) {
        for (int i=1;i<=m;i++) {
            cin >> p[i];
        }
        p[++m] = n;
        
        
        for (int i=1;i<=m;i++) {
            dp[i][i] = 0;
            tr[i][i] = i;
        }
        for (int len=2;len<=m;len++) {
            for (int l=1;l+len-1<=m;l++) {
                int r = l+len-1;
                dp[l][r] = 0x3f3f3f3f;
                for (int t=tr[l][r-1];t<=tr[l+1][r];t++) {
                    if (dp[l][t] + dp[t+1][r] < dp[l][r]) {
                        dp[l][r] = dp[l][t] + dp[t+1][r];
                        tr[l][r] = t;
                    }
                }
                dp[l][r] += p[r] - p[l-1];
            }
        }

        cout << dp[1][m] << endl;
    }
}