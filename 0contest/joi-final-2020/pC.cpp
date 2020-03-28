#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#define eb emplace_back
#define X first
#define Y second
#define MEM(i,a) memset(i,(a),sizeof(i))
#ifdef tmd
#define debug(...) fprintf(stderr,"%d(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){
    cerr<<x<<",";
    _do(y...);
}
#define IOS()
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define pary(...)
#define endl '\n'
#endif // tmd

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 3003;

int n, m;
char c[MAXN][MAXN];
bool d[MAXN][MAXN];
bool w[MAXN][MAXN];

int dp[2][3];

bool valid (int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}
int main () {
    IOS();

    cin >> n >> m;
    REP (i, n) {
        REP (j, m) {
            cin >> c[i][j];
        }
    }

    REP (i, n) {
        REP (j, m-2) {
            if (c[i][j] == 'R' && c[i][j+1] == 'G' && c[i][j+2] == 'W') {
                d[i][j+1] = true;
                debug(i, j+1);
            }
        }
    }

    REP (j, m) {
        REP (i, n-2) {
            if (c[i][j] == 'R' && c[i+1][j] == 'G' && c[i+2][j] == 'W') {
                w[i+1][j] = true;
                debug(i+1, j);
            }
        }
    }

    int ans = 0;
    REP (i, n+m+4) {
        int x = i;
        int y = 0;

        MEM(dp, 0);
        debug(x);
        while (x >= 0 && y < m) {
            if (valid(x,y) && w[x][y]) {
                dp[y&1][1] = max(dp[(y&1)^1][0], dp[(y&1)^1][1]) + 1;
            } else {
                dp[y&1][1] = 0;
            }
            if (valid(x,y) && d[x][y]) {
                dp[y&1][2] = max(dp[(y&1)^1][0], dp[(y&1)^1][2]) + 1;
            } else {
                dp[y&1][2] = 0;
            }
            dp[y&1][0] = max({dp[(y&1)^1][1], dp[(y&1)^1][2], dp[(y&1)^1][0]});
            x--;
            y++;
        }

        ans += max({dp[y&1^1][0], dp[y&1^1][1], dp[y&1^1][2]});
    }

    cout << ans << endl;


    return 0;
}
/*
3 4
RGWG
GRGW
RGWR

*/
