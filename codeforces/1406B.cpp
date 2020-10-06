#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;

const int MAXN = 100005;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll mx[6][MAXN], mn[6][MAXN];
int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i=0; i<6; i++) for (int j=0; j<n+1; j++) mx[i][j] = -INF;
        for (int i=0; i<6; i++) for (int j=0; j<n+1; j++) mn[i][j] = INF;
        mx[0][0] = 1;
        mn[0][0] = 1;

        for (int i=1; i<=n; i++) {
            ll x;
            cin >> x;
            mx[0][i] = 1;
            mn[0][i] = 1;
            for (int j=1; j<=5; j++) {
                mx[j][i] = mx[j][i-1];
                mn[j][i] = mn[j][i-1];
                if (mx[j-1][i-1] != -INF) {
                    mx[j][i] = max(mx[j][i], mx[j-1][i-1] * x);
                    mn[j][i] = min(mn[j][i], mx[j-1][i-1] * x);
                }
                if (mn[j-1][i-1] != INF) {
                    mn[j][i] = min(mn[j][i], mn[j-1][i-1] * x);
                    mx[j][i] = max(mx[j][i], mn[j-1][i-1] * x);
                }
            }
        }
        cout << mx[5][n] << endl;

    }

}
