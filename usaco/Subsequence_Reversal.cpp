#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#define MX(i,j) i=max(i, j)
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 51;
const ll MOD = 1000000007;

int n, dp[MAXN][MAXN][MAXN][MAXN], a[MAXN];

int solve (int l, int r, int p, int s) {
    int &cur = dp[l][r][p][s];
    if (cur != -1) {
        return cur;
    }
    cur = 0;
    if (p > s) {
        return cur = -MOD;
    }
    if (l == r) {
        return cur = (a[l] >= p && a[r] <= s) ? 1 : 0;
    }
    if (l > r) {
        return cur = 0;
    }

    MX(cur, solve(l+1, r-1, p, s));
    // swap a[l], a[r]
    if (a[r] >= p) {
        MX(cur, solve(l+1, r-1, a[r], s) + 1);
    }
    if (a[l] <= s) {
        MX(cur, solve(l+1, r-1, p, a[l]) + 1);
    }
    if (a[l] <= s && a[r] >= p) {
        MX(cur, solve(l+1, r-1, a[r], a[l]) + 2);
    }

    MX(cur, solve(l, r-1, p, s));
    if (a[r] <= s) {
        MX(cur, solve(l, r-1, p, a[r]) + 1);
    }
    MX(cur, solve(l+1, r, p, s));
    if (a[l] >= p) {
        MX(cur, solve(l+1, r, a[l], s) + 1);
    }

    return cur;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

#ifndef tmd
    freopen("subrev.in", "r", stdin);
    freopen("subrev.out", "w", stdout);
#endif // tmd

    cin >> n;
    REP (i, n) {
        cin >> a[i];
    }

    memset(dp, -1, sizeof(dp));
    cout << solve(0, n-1, 0, 50) << endl;

}
