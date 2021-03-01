#include <iostream>
#include <algorithm>
using namespace std;
struct food {
    int c, e, s;
};
food fs[1000];
int dp[1001][11] = {};
int main() {
    int t, n, a;
    cin >> t >> n >> a;
    for (int i = 0; i < n; ++i) {
        cin >> fs[i].c >> fs[i].e >> fs[i].s;
    }
    for (int i = 0; i < n; ++i) {
        int c = fs[i].c, e = fs[i].e, s = fs[i].s;
        for (int j = c; j <= t; ++j) {
            for (int k = 0; k <= a; ++k) {
                dp[j][k] = max(dp[j][k], dp[j-1][min(k+1, a)]);
                // if (k >= 1) dp[j][k] = max(dp[j][k], dp[j][k-1]);
                if (k >= e) dp[j][k] = max(dp[j][k], dp[j - c][min(k+c-e, a)] + s);
            }
        }
        // for (int j = 0; j <= t; ++j) {
        //     cout << j << "  ";
        //     for (int k = 0; k <= a; ++k) {
        //         cout << dp[j][k] << " \n"[k==a];
        //     }
        // }
        // cout << endl;
    }
    cout << dp[t][0] << endl;
}

