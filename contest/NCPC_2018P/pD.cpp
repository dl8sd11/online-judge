#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define MEM(a,b) memset(a,(b),sizeof(a))
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#define eb emplace_back
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d (%s) = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<",";_do(y...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define debug(...)
#define endl '\n'
#endif

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;

ll n;

ll extGCD (ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll xp, yp;
    ll res = extGCD(b,a%b,xp,yp);
    x = yp;
    y = xp-a/b*yp;
    return res;
}
int main () {
    IOS();

    cin >> n;
    while (n--) {
        ll a, p, r;
        cin >> a >> r >> p;
        ll x, y;
        ll res = extGCD(a,p,x, y);
        debug(x, y, res);
        x = ((x%p)+p) % p;
        cout << x * r % p << endl;
    }
}
