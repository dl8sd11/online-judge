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

const int MAXN = 202;
const ll MOD = 1000000007;


int dp[MAXN][MAXN];
int lcs (vector<int> a, vector<int> b) {

    memset(dp, 0, sizeof(dp));
    for (int i=1; i<=SZ(a); i++) {
        for (int j=1; j<=SZ(b); j++) {
            dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            if (a[i-1] == b[j-1]) {
                dp[i][j] = max(dp[i][j], dp[i-1][j-1]+1);
            }
        }
    }

    return dp[SZ(a)][SZ(b)];


}
/*********************GoodLuck***********************/
int main () {
    IOS();

    int n, m, cnt = 0;
    while (cin >> n >> m && n*m > 0) {
        vector<int> a;
        vector<int> b;

        REP (i, n) {
            int d;
            cin >> d;
            a.eb(d);
        }

        REP (i, m) {
            int d;
            cin >> d;
            b.eb(d);
        }

        cnt++;
        cout << "Twin Towers #" << cnt << endl;

        cout << "Number of Tiles : " << lcs(a, b) << endl;

        cout << endl;
    }

}

