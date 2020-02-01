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

const int MAXN = 100005;
const ll MOD = 1000000007;

int t, a, b, c, d, k;
int mu[MAXN], pre[MAXN];
bool sieve[MAXN];
vector<int> prime;

void build () {
    mu[1] = 1;
    for (int i=2; i<MAXN; i++) {
        if (!sieve[i]) {
            prime.emplace_back(i);
            mu[i] = -1;
        }
        for (int j=0; j<SZ(prime) && i*prime[j]<MAXN; j++) {
            sieve[i*prime[j]] = true;
            if (i % prime[j] == 0) {
                mu[i*prime[j]] = 0;
                break;
            }
            mu[i*prime[j]] = mu[i] * mu[prime[j]];
        }
    }

    REP1 (i, MAXN-1) {
        pre[i] = pre[i-1] + mu[i];
    }
}

ll solve (int n, int m) {
    ll ret = 0;
    for (int i=1, la; i<=n; i=la+1) {
        la = min(n/(n/i), m/(m/i));
        ret += ll(pre[la] - pre[i-1]) * (n/i) * (m/i);
    }
    return ret;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    build();
    cin >> t;
    REP1 (ts, t) {
        cin >> a >> b >> c >> d >> k;
        if (k == 0) {
            cout << "Case " << ts << ": 0" << endl;
        } else {
            if (b > d) {
                swap(b, d);
            }
            bool x = (b >= k);
            cout << "Case " << ts << ": " << solve(b/k, d/k) - (solve(b/k, b/k) - x) / 2  << endl;
        }
    }

    return 0;
}
