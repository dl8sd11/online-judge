#include <bits/stdc++.h>
using namespace std;

int n,v,ans,tk;
int main () {
    cin >> n >> v;
    for (int i=1;i<=n;i++) {
        if (tk < n-i) {
            int d = min(v-tk,n-i);
            tk += d;
            ans += d*i;
        }
        tk--;
    }

    cout << ans << endl;
}