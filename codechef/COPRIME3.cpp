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

const int MAXN = 1000006;
const ll MOD = 1000000007;

int n, cnt[MAXN], c[MAXN], mu[MAXN];
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

pair<__int128,__int128> solve () {
    pair<__int128,__int128> ret;
    REP1 (i, MAXN-1) {
        ret.first += __int128(c[i])*c[i]*mu[i];
        ret.second += __int128(c[i])*c[i]*c[i]*mu[i];
    }
    return ret;
}

#ifdef tmd
vector<int> v;
#endif
/*********************GoodLuck***********************/
int main () {
    IOS();

    build();

    cin >> n;
    REP (i, n) {
        int a;
        cin >> a;
#ifdef tmd
        v.emplace_back(a);
#endif
        cnt[a]++;
    }
    for (int i=1; i<MAXN; i++) {
        for (int j=i; j<MAXN; j+=i) {
            c[i] += cnt[j];
        }
    }

    pair<__int128,__int128> ans = solve();
    //debug(ans.first, ans.second);

#ifdef tmd
    int two = 0, three = 0;
    REP (i, n) {
        REP (j, n) {
            REP (k, n) {
                three += __gcd(__gcd(v[i], v[j]), v[k]) == 1;
            }
        }
    }

    REP (i, n) {
        REP (j, n) {
                two += __gcd(v[i], v[j]) == 1;
        }
    }

    debug(two, three);

#endif

    cout << ll((ans.second - ans.first * 3 + cnt[1] * 2) / 6) << endl;
    return 0;
}
