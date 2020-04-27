#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 100005;
const int MAXK = 202;

int n, k ,a[MAXN], p[MAXN];
ll dp[2][MAXN];
int tr[MAXK][MAXN];

void chmx (int &x, int y) {
    x = x > y ? x : y;
}

void tran (int i, int j, int l) {
    ll nw = dp[(l&1)^1][j] + 1LL * (p[i] - p[j]) * p[j];
    if (dp[l&1][i] <= nw) {
        tr[l][i] = j;
        dp[l&1][i] = nw;
    }
}

void solve (int nL, int nR, int tL, int tR, int kd) {
    if (nL > nR) {
        return;
    }
    if (tL == tR) {
        for (int i=nL; i<=nR; i++) {
            tran(i, tL, kd);
        }
    } else {
        int nM = (nL + nR) >> 1;
        for (int i=tL; i<=min(tR, nM-1); i++) {
            tran(nM, i, kd);
        }
        solve(nL, nM-1, tL, tr[kd][nM], kd);
        solve(nM+1, nR, tr[kd][nM], tR, kd);
    }
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;
    for (int i=1; i<=n; i++) {
        cin >> a[i];
        p[i] = a[i] + p[i-1];
    }

    for (int i=1; i<=k; i++) {
        solve(1, n, 0, n, i);
    }

    cout << dp[k&1][n] << endl;

    for (int i=k; i>=1; i--) {
        cout << tr[i][n] << " \n"[i==1];
        n = tr[i][n];
    }

    return 0;
}
