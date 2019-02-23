#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,a[300002],pre[300002];
map<ll,int> cnt[2];
int main () {
    cin >> n;
    for (int i=1;i<=n;i++) {
        cin >> a[i];
        pre[i] = pre[i-1] ^ a[i];
    }

    ll ans = 0;
    for (int i=0;i<=n;i++) {
        cnt[i&1][pre[i]]++;
        ans += cnt[i&1][pre[i]] - 1;
    }

    cout << ans << endl;
}