#include <bits/stdc++.h>
#include <ctime>
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

const int MAXN = 81;
const ll MOD = 1000000007;

int n, k, dis[MAXN][MAXN];

bool part[MAXN];
int dp[2][MAXN];
int solve () {

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;

    for (int i=0; i<n; i++) {
        part[i] = rand() % 2;
    }
    part[0] = 1;

    for (int i=1; i<=k; i++) {
        for (int j=0; j<n; j++) {
            int res = MOD;
            if (part[j] ^ (i&1)) {
                for (int l=0; l<n; l++) {
                    res = min(res, dp[(i&1)^1][l] + dis[l][j]);
                }
            }
            dp[i&1][j] = res;
        }
    }

    return dp[k&1][0];
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    srand(time(0));

    cin >> n >> k;
    REP (i, n) {
        REP (j, n) {
            cin >> dis[i][j];
        }
    }

    int ans = MOD;
    while (double(clock() / CLOCKS_PER_SEC < 2.9)) {
        ans = min(ans, solve());
    }

    cout << ans << endl;
}

