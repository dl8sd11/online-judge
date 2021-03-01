#include <bits/stdc++.h>
using namespace std;

void cmax (int &x, int y) {
    x = max(x, y);
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t, n, a;
    cin >> t >> n >> a;

    vector<int> c(n), e(n), s(n);
    for (int i=0; i<n; i++) {
        cin >> c[i] >> e[i] >> s[i];
    }

    vector<vector<int> > dp(t+1, vector<int>(a+1, 0));


    for (int i=0; i<n; i++) {
        if (e[i] > c[i]) {
            for (int j=0; j<=t-c[i]; j++) {
                for (int k=0; k<=a; k++) {
                    for (int f=0; f<=a; f++) {
                        if (j+c[i]+f <= t && k+(e[i]-c[i])-f <= a) {
                            cmax(dp[j+c[i]+f][max(e[i],k+(e[i]-c[i])-f)], dp[j][k] + s[i]);
                        }
                    }
                }
            }
        } else {
            for (int j=0; j<=t-c[i]; j++) {
                for (int k=a; k>=0; k--) {
                    for (int f=0; f<=a; f++) {
                        if (j+c[i]+f <= t && k+(e[i]-c[i])-f <= a) {
                            cmax(dp[j+c[i]+f][max(e[i],k+(e[i]-c[i])-f)], dp[j][k] + s[i]);
                        }
                    }
                }
            }
        }

        //cout << "============" << endl;
        //for (int j=0; j<=t; j++) {
            //for (int k=0; k<=a; k++) {
                //cout << dp[j][k] << ",";
            //}
            //cout << endl;
        //}
        //cout << "===========" << endl << endl;

    }

    

    int ans = 0;
    for (int i=0; i<=t; i++) {
        for (int j=0; j<=min(a, t-i); j++) {
            cmax(ans, dp[i][j]);
        }
    }
    cout << ans << endl;
}
