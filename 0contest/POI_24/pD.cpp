#include <bits/stdc++.h>
using namespace std;
#include "ckuclib.h"
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

const int MAXN = 50004;
const ll MOD = 1000000007;
const int MAXE = 15;
const int MAXM = 1500;

int cost[MAXN][3];
int dp[MAXN][MAXE+1];

#ifdef tmd
int pd[MAXN][MAXM+3];
#endif // tmd


void ckmin (int &x, int y) {
    x = min(x, y);
}

map<int,int> dp;

int main () {
    srand(time(0));

    int itr;

    #ifdef tmd
    itr = 10000;
    #else
    itr = 1;
    #endif // tmd
    REP (_, itr) {
        int n = dajn();
        int e = daje();
//        debug(n, e);

        REP1 (i, n) {
            cost[i][0] = jedno(i);
            cost[i][1] = dwa(i);
            cost[i][2] = polowa(i);
//            pary(cost[i], cost[i]+3);
        }

        memset(dp, 0x3f, sizeof(dp));
        REP (i, MAXE) {
            dp[0][i] = 0;
        }

        REP1 (i, n) {
            if (i >= 2) {
                ckmin(dp[i][MAXE-1], dp[i-i/2][MAXE-1] + cost[i][2]);
            }
            ckmin(dp[i][MAXE-1], dp[i-1][MAXE-1] + cost[i][0]);
            REP (j, MAXE) {
                if (j < MAXE - 1) {
                    ckmin(dp[i][j], dp[i-1][j+1] + cost[i][0]);
                }
                if (i >= 2) {
                    ckmin(dp[i][j], dp[i-2][j] + cost[i][1]);
                }
                if (i >= 2 && j > 0) {
                    ckmin(dp[i][j], dp[i-i/2][j-1] + cost[i][2]);
                }
            }
        }

        int ans = dp[n][min(e, MAXE-1)];

    #ifdef tmd

        memset(pd, 0x3f, sizeof(pd));
        REP (i, MAXM) {
            pd[0][i] = 0;
        }

        REP1 (i, n) {
            REP (j, MAXM) {
                ckmin(pd[i][j], pd[i-1][j+1] + cost[i][0]);
                if (i >= 2) {
                    ckmin(pd[i][j], pd[i-2][j] + cost[i][1]);
                }
                if (i >= 2 && j > 0) {
                    ckmin(pd[i][j], pd[i-i/2][j-1] + cost[i][2]);
                }
            }
        }

        int ans2 = pd[n][e];
        debug(ans, ans2);

        if (ans != ans2) {
            debug(n, e);
            REP1 (i, n) {
                pary(cost[i], cost[i]+3);
            }
        }

        assert(ans == ans2);
    #endif // tmd

        odpowiedz(ans);

    }
}
