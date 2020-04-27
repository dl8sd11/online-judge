#include <bits/stdc++.h>
using namespace std;

const int MAXL = 1003;

double dp[MAXL];
int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);

    int n, k;
    cin >> n >> k;

    for (int i=1; i<=n; i++) {
        for (int j=1; j<MAXL-1; j++) {
            dp[j] = 1.0/k/(j+1)*(dp[j+1]+j*dp[j]+(j+3.0)*j/2)\
                    +(k-1.0)/k*dp[j];
        }
    }

    cout << fixed << setprecision(12) << dp[1]*k << endl;

    return 0;
}
