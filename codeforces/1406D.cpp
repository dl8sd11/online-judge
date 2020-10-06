#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n;
vector<ll> a, d;

void make (ll D, ll &x, ll &y, int ml) {
    if (D > 0) x += ml * D;
    else if (D < 0) y -= ml * D;
}

ll solve (ll add, ll sub, ll start) {
    ll L = -INF, R = INF;
    while (L < R - 1) {
        ll M = (L + R) >> 1;
        if (start-M+add <= M) R = M;
        else L = M;

    }
    return R;
}
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    a.resize(n);
    d.resize(n+1);

    ll add = 0, sub = 0;
    for (int i=0; i<n; i++) {
        cin >> a[i];
        if (i) d[i] = a[i] - a[i-1];
        make(d[i], add, sub, 1);
    }

    int q;
    cin >> q;
    cout << solve(add, sub, a[0]) << '\n';

    while (q--) {
        ll x, l, r;
        cin >> l >> r >> x;
        if (l == 1) {
            a[0] += x;
        }
        if (l>1) make(d[l-1], add, sub, -1);
        d[l-1] += x;
        if (l>1) make(d[l-1], add, sub, 1);
        if (r<n) make(d[r], add, sub, -1);
        d[r] -= x;
        if (r<n) make(d[r], add, sub, 1);
        cout << solve(add, sub, a[0]) << '\n';
    }
}

