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

const int MAXN = 15000007;
const ll MOD = 1000000007;

int mu[MAXN], fac[MAXN];
bool sieve[MAXN];
int prime[970705], cnt;

int mpow (ll bs, int ep) {
    int ret = 1;
    while (ep) {
        if (ep & 1) {
            ret = bs * ret % MOD;
        }
        bs = bs * bs % MOD;
        ep >>= 1;
    }
    return ret;
}

void build () {
    mu[1] = 1;
    fac[0] = fac[1] = 1;
    for (int i=2; i<MAXN; i++) {
        fac[i] = ll(fac[i-1]) * i % MOD;
        if (!sieve[i]) {
            prime[cnt++] = i;
            mu[i] = -1;
        }
        for (int j=0; j<cnt && i*prime[j]<MAXN; j++) {
            sieve[i*prime[j]] = true;
            if (i % prime[j] == 0) {
                mu[i*prime[j]] = 0;
                break;
            }
            mu[i*prime[j]] = mu[i] * mu[prime[j]];
        }
    }
    REP1 (i, MAXN-1) {
        mu[i] += mu[i-1];
    }
}

int f (int n, int m) {
    int ret = 0;
    for (int i=1,la; i<=min(n, m); i=la+1) {
        int ni = n/i, mi = m/i;
        la = min(n/ni, m/mi);
        ret = (ll(ret) + ll(ni) * mi * (mu[la] - mu[i-1])) % (MOD-1);
    }
    if (ret < 0) {
        ret += (MOD-1);
    }
    return ret;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    build();

    int n, m;
    cin >> n >> m;

    ll ans = 1;
    for (int i=1,la; i<=min(n, m); i=la+1) {
        int ni = n/i, mi = m/i;
        la = min(n/ni, m/mi);
        int res = f(ni, mi);

        ans = ans * mpow(ll(fac[la]) * mpow(fac[i-1], MOD-2) % MOD, res) % MOD;
    }
#ifdef tmd
    REP1 (i, n) {
        debug(mu[i] - mu[i-1]);
    }
    ll ret = 1;
    ll test = 0;
    REP1 (i, n) {
        REP1 (j, m) {
            test += __gcd(i, j) == 1;
            ret = ret * __gcd(i, j) % MOD;
        }
    }
    debug(f(n, m), test);
    debug(ret);
#endif

    cout << ans << endl;
    return 0;
}
