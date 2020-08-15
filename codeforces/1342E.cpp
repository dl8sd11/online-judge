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
const ll MOD = 998244353 ;

int n, k;
ll f[MAXN], r[MAXN];

ll mpow (ll bs, ll ep) {
    ll ret = 1;
    while (ep) {
        if (ep&1) {
            ret = ret * bs % MOD;
        }
        bs = bs * bs % MOD;
        ep >>= 1;
    }
    return ret;
}

ll C (ll m, ll p) {
    return f[m] * r[p] % MOD * r[m-p] % MOD;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;

    f[0] = r[0] = 1;
    for (int i=1; i<=n; i++) {
        f[i] = f[i-1] * i % MOD;
        r[i] = mpow(f[i], MOD-2);
    }

    ll c = n - k;
    if (c <= 0) {
        cout << 0 << endl;
        return 0;
    }

    ll ans = 0;
    for (int i=0; i<c; i++) {
        ll add =  C(c,i) * mpow(c-i, n) % MOD;
        if (i&1) {
            add = MOD - add;
        }
        ans = (ans + add) % MOD;
    }

    cout << (k?2:1) * ans * C(n,c) % MOD << endl;
}

