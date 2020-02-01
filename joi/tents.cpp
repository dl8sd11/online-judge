#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
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

const int MAXN = 3003;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll h, w;
ll dp[MAXN][MAXN];
ll fac[MAXN], pw[MAXN], rfac[MAXN];

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

ll single (ll x, ll y) {
    if (dp[x][y] != 0) {
        return dp[x][y];
    }
    if (x == 0 || y == 0) {
        return dp[x][y] = 1;
    }
    return dp[x][y] = (single(x-1,y) + single(x-1,y-1)*4*y) % MOD;
}

ll cob (ll n, ll r) {
    return fac[n] * rfac[r] % MOD * rfac[n-r] % MOD;
}

ll pa[MAXN];
ll duo1 (ll len, ll one, ll two) {
    return cob(len,one) * cob(len-one,two*2) % MOD * pa[two] % MOD;
}

ll duo2 (ll len, ll one, ll two) {
    return fac[len] * rfac[len-(one+two*2)] % MOD * pw[two] % MOD;
}

/*********************GoodLuck***********************/
signed main () {
    IOS();

    cin >> h >> w;

    fac[0] = pw[0] = rfac[0] = 1;
    pa[0] = 1;

    ll r2 = mpow(2, MOD-2);
    REP1 (i, MAXN-1) {
        fac[i] = fac[i-1] * i % MOD;
        rfac[i] = mpow(fac[i], MOD - 2);
        pw[i] = pw[i-1] * r2 % MOD;
        pa[i] = pa[i-1] * (i*2-1) % MOD;
    }

    debug(cob(5,2));

    ll ans = MOD-1;
    REP (i, h+1) {
        REP (j, w+1) {
            if (i+j*2<=h && i*2+j <= w) {
                ll cur = single(h-(i+j*2),w-(i*2+j));
                cur = cur * duo1(h,i,j) % MOD;
                cur = cur * duo2(w,j,i) % MOD;
                ans = (ans + cur) % MOD;

                debug(i, j);
                assert(duo1(h,i,j)*duo2(w,j,i)%MOD == duo2(h,i,j)*duo1(w,j,i)%MOD);
            }
        }
    }


    cout << ans << endl;
}
