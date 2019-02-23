#include <bits/stdc++.h>
using namespace std;

int n,preo[200004],pree[200004],a[200004];
int main () {
    cin >> n;
    for (int i=1;i<=n;i++) {
        cin >> a[i];
        preo[i] += preo[i-1];
        pree[i] += pree[i-1];
        if (i&1) {
            preo[i] += a[i];
        } else {
            pree[i] += a[i];
        }
    }
    int ans = 0;
    for (int i=1;i<=n;i++) {
        int o = preo[i-1] + (pree[n] - pree[i]);
        int e = pree[i-1] + (preo[n] - preo[i]);
        if (o == e) {
            ans++;
        }
    }

    cout << ans << endl;
}