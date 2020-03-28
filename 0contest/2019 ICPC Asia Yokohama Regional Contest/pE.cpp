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

const int MAXN = 5003;
const ll MOD = 1000000007;

int n, m, a[MAXN], dp[MAXN][MAXN][2], mx;
array<int,2> tp;

void add (int &x, int y) {
    x += y;
    if (x >= MOD) {
        x-= MOD;
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;

    dp[0][0][0] = 1;
    REP1 (i, n) {
        cin >> a[i];
        debug(i, mx, tp[0], tp[1]);

        if (mx == i-1) {
            if (a[i] == mx + 1) {
                for (int j=0; j<=i; j++) {
                    if (j > 0) {
                        add(dp[i][j][0], dp[i-1][j-1][0]);
                    }
                    add(dp[i][j][0], dp[i-1][j][0]);
                }
            } else {
                for (int j=0; j<=i; j++) {
                    if (j > 0) {
                        add(dp[i][j][0], dp[i-1][j-1][0]);
                    }
                    add(dp[i][j][1], dp[i-1][j][0]);
                }
            }
            tp[0] = a[i];

            debug("fre");
        } else {
            if (a[i] > mx) {
                for (int j=0; j<=i; j++) {
                    if (j > 0) {
                        add(dp[i][j][0], dp[i-1][j-1][0]);
                    }
                    add(dp[i][j][1], dp[i-1][j][1]);
                }

                tp[0] = a[i];
                debug("inc");
            } else {
                if (a[i] < tp[1]) {
                    cout << 0 << endl;
                    return 0;
                }

                debug("dec");
                if (mx == i) {
                    debug("unlock");
                    for (int j=0; j<=i; j++) {
                        if (j > 0) {
                            add(dp[i][j][0], dp[i-1][j-1][1]);
                        }
                        add(dp[i][j][0], dp[i-1][j][0]);
                    }
                } else {
                    for (int j=0; j<=i; j++) {
                        if (j > 0) {
                            add(dp[i][j][1], dp[i-1][j-1][1]);
                        }
                        add(dp[i][j][0], dp[i-1][j][0]);
                    }
                }

                tp[1] = a[i];

            }
        }

        mx = max(mx, a[i]);
    }

    int ans = 0;
    for (int i=0; i<=m; i++) {
        assert(dp[n][i][1] == 0);
        if (n-i <= m) {
            add(ans, dp[n][i][0]);
        }
    }

    cout << ans << endl;

    #ifdef tmd

    int a, b, c;
    while (cin >> a >> b >> c) {
        cout << dp[a][b][c] << endl;
    }

    #endif // tmd
}
