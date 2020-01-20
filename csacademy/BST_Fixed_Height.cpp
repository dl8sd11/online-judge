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


const int MAXN = 502;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, h;
ll dp[MAXN][MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> h;

    dp[0][0] = 1;
    REP1 (i, MAXN-1) {
        dp[0][i] = 1;
        dp[1][i] = 1;
    }

    for (int i=2;i<=n;i++) {
        for (int j=1;j<=h;j++) {
            for (int l=0;l<i;l++) {
                int r = i-l-1;
                dp[i][j] += dp[l][j-1] * dp[r][j-1] % MOD;
                dp[i][j] %= MOD;
            }
        }
    }

    cout << (dp[n][h] - dp[n][h-1] + MOD) % MOD << endl;

}
