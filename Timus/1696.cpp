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

const int MAXN = 1003, MAXK = 202;

int n, k, p;
int dp[2][MAXK][MAXK], lpre[MAXK][MAXK], rpre[MAXK][MAXK];

void add (int &x, int y) {
    x += y;
    if (x >= p) {
        x -= p;
    }
}

int sub (int x, int y) {
    x -= y;
    if (x < 0) {
        x += p;
    }
    return x;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n >> k >> p;



    int ans = 0;
    REP1 (i, k) {
        dp[1][0][i] = 1;
    }
    for (int i=2; i<=n; i++) {
        REP (l, MAXK) {
            REP (j, MAXK) {
                dp[i&1][l][j] = 0;
            }
        }

        REP (l, MAXK) {
            int sum = 0;
            REP (j, MAXK) {
                add(sum, dp[i&1^1][l][j]);
                rpre[l][j] = sum;
            }
        }

        REP (j, MAXK) {
            int sum = 0;
            REP (l, MAXK) {
                add(sum, dp[i&1^1][l][j]);
                lpre[l][j] = sum;
            }
        }

        for (int u=1; u<=k; u++) {
            for (int l=0; l<u; l++) {
                dp[i&1][l][u] = dp[i&1^1][l][u];
                add(dp[i&1][l][u], sub(rpre[l][u-1], rpre[l][l]));

                if (l != 0) {
                    add(dp[i&1][l][u], lpre[l][u]);
                }
                debug(i, l, u, dp[i&1][l][u]);
            }
        }
    }

    REP (i, k+1) {
        REP (j, k+1) {
            add(ans, dp[n&1][i][j]);
        }
    }

    cout << ans + 1 << endl;
}
