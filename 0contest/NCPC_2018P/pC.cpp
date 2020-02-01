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
int main () {
    IOS();

    while (cin >> n && n) {
        ll bs = n;
        for (ll i=3; i*i<=n; i++) {
            if (n % i == 0) {
                if (i & 1) {
                    bs = min(bs, i);
                }
                if ((n/i) & 1) {
                    bs = min(bs, n/i);
                }
                break;
            }
        }

        debug(bs);
        ll ans = n / bs;

        ll a, b, c;
        if (bs == n && bs % 2 == 0) {
            ans = n / 4;
            a = ans;
            b = ans;
            c = ans * 2;
        } else {
            a = ans;
            b = c = ans * (bs/2);
        }
        assert(a+b+c == n);
        cout << a << " " << b << " " << c << endl;

    }

    return 0;
}
