#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SparseTable {
    int (*cmp) (int, int);
    vector<vector<int> > tbl;

    SparseTable (const vector<int> &a, int (*_cmp)(int, int)) {
        int N = int(a.size());
        int M = __lg(N) + 1;
        tbl.resize(M, vector<int>(N));
        tbl[0] = a;
        cmp = _cmp;

        for (int i=1; i<M; i++) {
            for (int j=0; j<N; j++) {
                if (j+(1<<i) <= N) {
                    tbl[i][j] = (*cmp)(tbl[i-1][j], tbl[i-1][j+(1<<i-1)]);
                }
            }
        }
    }

    int query (int l, int r) {
        int len = __lg(r-l);
        return cmp(tbl[len][l], tbl[len][r-(1<<len)]);
    }
};

int MN (int x, int y) {
    return x > y ? y : x;
}

int MX (int x, int y) {
    return x < y ? y : x;
}



int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;

    vector<int> h(n);
    for (int i=0; i<n; i++) {
        cin >> h[i];
    }

    SparseTable smin(h, MN), smax(h, MX);
    vector<int> match(n);

    for (int l=0,r=0; r<n; r++) {
        while (smax.query(l,r+1) - smin.query(l,r+1) > k) {
            l++;
        }
        match[r] = l;
    }

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;

        ll ans = 0;
        for (int i=l; i<r; i++) {
            ans += min(i-l+1, i-match[i]+1);
        }
        cout << ans << endl;
    }
}
