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

const int MAXN = 2003;
const ll MOD = 1000000007;

int dp[MAXN][MAXN];
int h[102], g[102];

void cmax (int &x, int y) {
    x = max(x, y);
}

int ce (int x, int y) {
    return (x + y - 1) / y;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    int p, q, n;
    cin >> p >> q >> n;

    for (int i=1; i<=n; i++) {
        cin >> h[i] >> g[i];
    }

    REP (i, MAXN) {
        REP (j, MAXN) {
            dp[i][j] = -MOD;
        }
    }
    dp[0][1] = 0;

    // meichen.yeh@gmail.com
    int ans = 0;

    for (int i=1; i<=n; i++) {
        int tower = ce(h[i], q);
            
        int rem = h[i] % q;
        if (rem == 0) {
            rem += q;
        }
        int me = ce(rem, p);

        for (int j=0; j<MAXN; j++) {

            if (j >= tower) {
                cmax(dp[i][j], dp[i-1][j-tower]);
            } 
            if (j-tower+1+me >= 0 && j-tower+1+me < MAXN) {
                cmax(dp[i][j], dp[i-1][j-tower+1+me] + g[i]);
            }

        }

        if (i == n) {
            for (int j=0; j<MAXN; j++) {
                cmax(ans, dp[i][j]);
            }
        }
    }

    cout << ans << endl;
    

}
/*
20 60 3
80 100
80 200
120 300
 */

