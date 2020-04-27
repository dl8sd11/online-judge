#include <bits/stdc++.h>
using namespace std;

int main () {
    int n, x, y;
    cin >> n >> x >> y;

    vector<int> ans(n, 0);

    for (int i=1; i<=n; i++) {
        for (int j=i+1; j<=n; j++) {

            int d = j-i;
            d = min(d, abs(i-x)+1+abs(j-y));
            d = min(d, abs(i-y)+1+abs(j-x));

            ans[d]++;
        }
    }

    for (int i=1; i<n; i++) {
        cout << ans[i] << endl;
    }
}
