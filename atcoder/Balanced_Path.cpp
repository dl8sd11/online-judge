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


const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 81;
bool dp[MAXN][MAXN][MAXN*MAXN*4];
const int hf = MAXN*MAXN*2;

int h, w, a[MAXN][MAXN], b[MAXN][MAXN];

/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> h >> w;
    REP (i, h) {
        REP (j, w) {
            cin >> a[i][j];
        }
    }
    REP (i, h) {
        REP (j, w) {
            cin >> b[i][j];
        }
    }

    dp[0][0][hf+a[0][0]-b[0][0]] = true;
    REP (i, h) {
        REP (j, w) {
            REP (u, 2) {
                swap(a[i][j], b[i][j]);
                int cur = a[i][j] - b[i][j];
                for (int k=0;k<MAXN*MAXN*4;k++) {
                    if (k-cur<0 || k-cur >= MAXN*MAXN*4) {
                        continue;
                    }
                    if (i > 0) {
                        dp[i][j][k] |= dp[i-1][j][k-cur];
                    }
                    if (j > 0) {
                        dp[i][j][k] |= dp[i][j-1][k-cur];
                    }
                }
            }
        }
    }

    int ans = 0x3f3f3f3f;
    REP (i, MAXN*MAXN*4) {
        if (dp[h-1][w-1][i]) {
            ans = min(ans, abs(i-hf));
        }
    }

    cout << ans << endl;
}
