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

const int MAXN = 500005;
const ll MOD = 1000000007;

int n, q, mu[MAXN];
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
}

int a[MAXN];
bool on[MAXN];
ll ans;
int cnt[MAXN];
int elm;

void upd (int d, int val) {
    ans -= ll(mu[d]) * cnt[d] * cnt[d];
    cnt[d] += val;
    ans += ll(mu[d]) * cnt[d] * cnt[d];
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    build();

    cin >> n >> q;
    REP (i, n) {
        cin >> a[i];
    }

    REP (u, q) {
        int x;
        cin >> x;
        x--;
        if (!on[x]) {
            elm+=a[x] == 1;
            for (int i=1; i*i<=a[x]; i++) {
                if (a[x] % i == 0) {
                    upd(i, 1);
                    if (i*i != a[x]) {
                        upd(a[x]/i, 1);
                    }
                }
            }
        } else {
            elm-=a[x] == 1;
            for (int i=1; i*i<=a[x]; i++) {
                if (a[x] % i == 0) {
                    upd(i, -1);
                    if (i*i != a[x]) {
                        upd(a[x]/i, -1);
                    }
                }
            }
        }
        on[x] ^= 1;
        debug(ans);
        cout << (ans - elm) / 2 << endl;
    }
    return 0;
}
