#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 200005;
const ll MOD = 1000000007;

int n;
ll T;
int t[MAXN];

ll done[MAXN];


ll mpow (ll bs, ll ep) {
    ll res = 1;
    while (ep) {
        if (ep & 1) {
            res = res * bs % MOD;
        }
        bs = bs * bs % MOD;
        ep >>= 1;
    }
    return res;
}

struct Combination {
    int n = -1, k = -1;

    ll res = 0;

    ll fac[MAXN], ifac[MAXN];

    ll cob (ll x, ll r) {
        assert (r <= x);
        return fac[x] * ifac[x-r] % MOD * ifac[r] % MOD;
    }

    void build () {
        fac[0] = ifac[0] = 1;
        for (int i=1; i<MAXN; i++) {
            fac[i] = fac[i-1] * i % MOD;
            ifac[i] = mpow(fac[i], MOD-2);
        }
    }

    Combination () {
        build();
    }

    ll count (int _n, int _k) {
        if (n == -1) {
            n = _n;
            k = _k;
            for (int i=0; i<=_k; i++) {
                res = (res + cob(n, i)) % MOD;
            }
        } else {
            res = (res * 2 - cob(n, k)) % MOD;
            if (res < 0) {
                res += MOD;
            }
            n++;

            assert(n == _n);
            while (_k > k) {
                res += cob(n, k+1);
                res %= MOD;
                k++;
            }

            while (_k < k) {
                res -= cob(n, k);
                res = (res + MOD) % MOD;
                k--;
            }

            assert(k == _k);
        }

        return res;
    }
};
/*********************GoodLuck***********************/
int main () {
    IOS();


    cin >> n >> T;

    for (int i=0; i<n; i++) {
        cin >> t[i];
    }

    ll pre = 0, base = 0, ans = 0;

    ll inv2 = mpow(2, MOD-2);
    Combination cob;
    for (int i=0; i<n; i++) {
        base = (base + t[i]);

        if (base > T) {
            break;
        }

        ll del = T - base;

        ll alive = 1;
        if (del < i+1) {
            alive = cob.count(i+1, del);
            debug(alive);
            alive = alive * mpow(inv2, i+1) % MOD;
            debug(i+1, del, alive);
        }

        ans = (ans + alive) % MOD;
    }

    cout << ans << endl;
}

