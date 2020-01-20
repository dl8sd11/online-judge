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

const int MAXN = 100005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int t, n, h;
bitset<MAXN> dp;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        dp.reset();
        dp[0] = true;

        cin >> n >> h;

        for (int i=0;i<n;i++) {
            int a, b, c;
            cin >> a >> b >> c;

            dp = (dp<<a) | (dp<<b) | (dp<<c);
        }

        int ans = -1;
        for (int i=h;i>=0;i--) {
            if (dp[i]) {
                ans = i;
                break;
            }
        }

        if (ans == -1) {
            cout << "no solution" << endl;
        } else {
            cout << ans << endl;
        }
    }

}
