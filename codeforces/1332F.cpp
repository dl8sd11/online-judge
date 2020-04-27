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

const int MAXN = 300005;
const ll MOD = 998244353;

int n;
vector<int> edge[MAXN];

int dp[3][2][MAXN];

void add (int &x, int y) {
    x = x + y >= MOD ? x + y - MOD : x + y;
}

void mul (int &x, int y) {
    x = 1LL * x * y % MOD;
}

void dfs (int nd, int pa) {
    for (auto v : edge[nd]) {
        if (v != pa) {
            dfs(v, nd);
        }
    }

    REP (i, 3) {
        REP (j, 2) {
            dp[i][j][nd] = 1;
        }
    }
    dp[0][1][nd] = 0;

    for (auto v : edge[nd]) {
        if (v != pa) {

            int sno = 0;
            add(sno, dp[0][0][v]);
            add(sno, dp[1][0][v]);
            add(sno, dp[2][0][v]);

            mul(dp[0][0][nd], sno);

            int sbo = 0;
            REP (i, 3) {
                REP (j, 2) {
                    add(sbo, dp[i][j][v]);
                }
            }

            mul(dp[1][1][nd], sbo);

            int sco = 0;
            REP (i, 3) {
                REP (j, 2) {
                    if (i != 2 || j != 1) {
                        add(sco, dp[i][j][v]);
                    }
                }
            }
            mul(dp[2][1][nd], sco);

            int xbo = 0;
            REP (i, 3) {
                add(xbo, dp[i][0][v]);
            }

            mul(dp[1][0][nd], xbo);
            mul(dp[2][0][nd], xbo);
        }
    }


    dp[1][0][nd] = (dp[1][1][nd] + MOD - dp[1][0][nd]) % MOD;
    dp[2][0][nd] = (dp[2][1][nd] + MOD - dp[2][0][nd]) % MOD;

    REP (i, 3) {
        REP (j, 2) {
            debug(i, j, nd, dp[i][j][nd]);
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    
    cin >> n;
    for (int i=0; i<n-1; i++) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    dfs(1, -1);

    int ans = MOD-1;
    add(ans, dp[0][0][1]);
    add(ans, dp[1][0][1]);
    add(ans, dp[2][0][1]);

    cout << ans << endl;
}

