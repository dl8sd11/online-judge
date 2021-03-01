#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

vector<int> a;
pii penalty (int k) {
    int n = a.size();
    pii ans = {0, 0}, pdp = {0, 0}, tr = {-1000000009, 0}, cur;
    for (int i=0; i<n; i++) {
        cur = max(pii(0, 0), pii(tr.first + a[i] - k, tr.second + 1));
        pdp = max(cur, pdp);
        tr = max(tr, pii(pdp.first - a[i], pdp.second));
    }
    swap(pdp.first, pdp.second);
    return pdp;
}

int main () {
    int n, k;
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;
    a.resize(n);
    for (int i=0; i<n; i++) cin >> a[i];

    pii opt = penalty(0);
    if (opt.first <= k) {
        cout << opt.second << endl;
        return 0;
    }

    int L = 10000007, R = -1;
    while (R < L - 1) {
        int M = (L + R) >> 1;
        if (penalty(M).first < k) L = M;
        else R = M;
    }

    pii res = penalty(R);
    cout << res.second + R * k << endl;
}
