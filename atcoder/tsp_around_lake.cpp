#include <bits/stdc++.h>
using namespace std;

int k, n, a[200005], mx;

int main () {
    cin >> k >> n;

    for (int i=0; i<n; i++) {
        cin >> a[i];
        if (i) {
            mx = max(mx, a[i] - a[i-1]);
        }
    }
    mx = max(mx, a[0] + k-a[n-1]);

    cout << k - mx << endl;
}
