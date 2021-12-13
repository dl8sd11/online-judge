#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<ll> wsum(n + 1);
    for (int i=0; i<m; i++) {
        int l, r, w;
        cin >> l >> r >> w;
        wsum[l - 1] += w;
        wsum[r] -= w;
    }

    ll acc = 0;
    for (int i=0; i<n; i++) {
        acc += wsum[i];
        wsum[i] = acc;
    }

    wsum.pop_back();
    sort(wsum.begin(), wsum.end());

    vector<int> t(n);
    for (int &x: t) cin >> x;
    sort(t.rbegin(), t.rend());

    ll ans = 0;
    for (int i=0; i<n; i++) {
        ans += t[i] * wsum[i];
    }

    cout << ans << endl;

}
