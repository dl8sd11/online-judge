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

const int MAXN = 400005;
const ll MOD = 1000000007;

ll mpow (ll bs, ll ep) {
    ll ret = 1;
    while (ep) {
        if (ep & 1) {
            ret = ret * bs % MOD;
        }
        bs = bs * bs % MOD;
        ep >>= 1;
    }
    return ret;
}

ll fac[MAXN], ifac[MAXN];

ll cob (ll n, ll r) {
    if (r < 0 || r > n) {
        return 0;
    }
    return fac[n] * ifac[r] % MOD *ifac[n-r] % MOD;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    fac[0] = ifac[0] = 1;
    REP1 (i, MAXN-1) {
        fac[i] = fac[i-1] * i % MOD;
        ifac[i] = mpow(fac[i], MOD-2);
    }

    int n, k;
    cin >> n >> k;
    k = min(k, n-1);

    ll ans = 0;
    for (int i=0; i<=k; i++) {
        ans += cob(n,i)*cob(n-1,n-i-1)%MOD;
        ans %= MOD;
    }

    cout << ans << endl;
}
