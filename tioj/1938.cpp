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

const int MAXN = 202;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

#define MX(a,b) a=max(a,b)
typedef long long ull;

int m, n, a, b , c, d;
inline ull calc (ull i, ull x, ull y) {
    x--,y--,i--;
    return (i*a + b*x + c*y) % d;
}


ull dp[2][101][MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> m >> n >> a >> b >> c;
    cin >> d;

    ull ans = 0;
    REP1 (i, n) {
        REP (y, m+1) {
            dp[0][i][y] = -INF;
        }
    }

    REP1 (x, m) {
        REP1 (i, n) {
            ull mx = 0;
            REP1 (y, m) {
                dp[x&1][i][y] = dp[(x&1)^1][i][y];
                MX(mx, dp[(x&1)^1][i-1][y-1]);
                MX(dp[x&1][i][y], mx+calc(i,x,y));
                if (i == n) {
                    MX(ans, dp[x&1][i][y]);
                }
            }
        }
    }

    cout << ans << endl;
}
