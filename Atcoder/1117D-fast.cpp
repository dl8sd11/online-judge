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

const int MAXN = 502;
const ll MOD = 1000000007;

ll n;
int m;

ll mod[MAXN*2], bs[MAXN*2], ans[MAXN*2], res[MAXN*2], dp[MAXN];
void mul(ll *p, ll *q) { // p *= q
    memset(res, 0, sizeof(res));
    REP (i, m) {
        REP (j, m) {
            res[i+j] += p[i] * q[j] % MOD;
            res[i+j] %= MOD;
        }
    }

    for (int i=m+m-2; i>=m-1; i--) {
        if (res[i]) {
            ll cof = res[i];
            for (int j=0; j<m; j++) {
                res[i-j] = (res[i-j] + cof*mod[m-1-j]) % MOD;
            }
        }
    }

    REP (i, m) {
        p[i] = res[i];
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;

    mod[0] = mod[m-1] = 1;
    mod[m] = MOD - 1;
    m++;

    ans[0] = bs[1] = 1;
    while (n) {
        if (n&1) {
            mul(ans, bs);
        }
        mul(bs, bs);
        n >>= 1;
    }
#ifdef tmd
    REP (i, m) {
        cout << ans[i] << " ";
    } cout << endl;
#endif

    if (n >= m) {
        cout << 1 << endl;
    } else {
        ll sum = 0;
        REP (i, m) {
            sum = (sum + ans[i]) % MOD;
        }
        cout << sum << endl;
    }


}
