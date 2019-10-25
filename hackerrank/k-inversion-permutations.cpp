#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
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

const int MAXN = 200005;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;
const int MAXM = 452;

int n, k, m, fac[MAXN], ifac[MAXN], dp[MAXN][MAXM];

int mpow (ll bs, int ep) {
    int ret =1;
    while (ep) {
        if (ep & 1) {
            ret = ret * bs % MOD;
        }
        bs = bs * bs % MOD;
        ep >>= 1;
    }
    return ret;
}

void add (int &x, int y) {
    x += y;
    if (x >= MOD) {
        x -= MOD;
    }
}

void sub (int &x, int y) {
    x -= y;
    if (x < 0) {
        x += MOD;
    }
}

void build () {
    fac[0] = ifac[0] = 1;
    REP1 (i, MAXN - 1) {
        fac[i] = 1LL * fac[i-1] * i % MOD;
        ifac[i] = mpow(fac[i], MOD - 2);
    }

    dp[0][0] = 1;
    REP1 (i, MAXN - 1) {
        REP1 (j, MAXM - 1) {
            if (i >= j) {
                add(dp[i][j], dp[i-j][j]);
                add(dp[i][j], dp[i-j][j-1]);
            }
            if (i >= (n+1)) {
                sub(dp[i][j], dp[i-n-1][j-1]);
            }
        }
    }

}

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;
    m = 1;
    for (int ac=0; ac<k; ac+=m, m++);
    debug(m);

    build();

    debug(fac[5]);
    int ans = 0;
    for (int s=0; s<=k; s++) {
        int cob = 1LL * fac[n-1+k-s] * ifac[n-1] % MOD * ifac[k-s] % MOD;
        debug(n-1, k-s);
        debug(s, cob);
        int sum = 0;
        for (int i=0; i<m; i++) {
            debug(i, dp[s][i]);
            if (i & 1) {
                sub(sum, 1LL * dp[s][i] * cob % MOD);
            } else {
                add(sum, 1LL * dp[s][i] * cob % MOD);
            }
        }
        add(ans, sum);
    }

    cout << ans << endl;
    return 0;
}
