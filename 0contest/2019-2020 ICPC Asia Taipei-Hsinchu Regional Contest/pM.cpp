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

const int MAXN = 100005;
const ll MOD = 1000000007;

ll m, n, d;

ll dmod (ll x) {
    while (x % d == 0) {
        x /= d;
    }
    return x % d;
}

ll fac (ll x) {
    ll res = 1;
    for (int i=1; i<=x; i++) {
        res *= i;
        res = dmod(res);
    }
    return res;
}

ll inv (ll x) {

    for (int i=1; i<d; i++) {
        if (dmod(i*x) == 1) {
            return i;
        }
    }
    debug(x);
    assert(false);
}

# ifdef tmd
ll nfac (ll x) {
    ll res = 1;
    for (int i=1; i<=x; i++) {
        res *= i;
    }
    return res;
}
# endif // tmd

ll mul (ll x, ll y) {
    return dmod(x*y);
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> m >> n >> d;
    debug(inv(6), inv(7), inv(2), inv(5));
    debug(mul(mul(inv(6), inv(7)), mul(inv(2), inv(5))));
    debug(dmod(410*525));


    debug(dmod(6*inv(3)), dmod(15*inv(5)));

    ll ans = dmod(dmod(fac(m) * inv(fac(n))) * inv(fac(m-n)));
    debug(ans);


    cout << ans << endl;

    #ifdef tmd
    ll tmp = 1;
    tmp = nfac(m) / nfac(n) / nfac(m-n);
    debug(tmp, dmod(tmp));
    #endif // tmd
}
