#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

#define X first
#define Y second

const int MAXN = 512;
const int MOD = 1000000007;

typedef pair<int, int> pii;

int n, m, dp[MAXN][MAXN][MAXN];
vector<pii> lim[MAXN];

bool vis[MAXN][MAXN][MAXN];
bool valid[MAXN][MAXN][MAXN];

inline void check (int r, int g, int b) {
    if (vis[r][g][b]) {
        if (!valid[r][g][b]) {
            dp[r][g][b] = 0;
        }
    } else {
        vis[r][g][b] = true;
        int dis[4] = {0, r, g, b};

        sort(dis, dis+4);

        for (auto p : lim[dis[3]]) {
            if (p.X > dis[4-p.Y] || p.X <= dis[4-p.Y-1]) {
                dp[r][g][b] = 0;
                valid[r][g][b] = false;
                return;
            }
        }

        valid[r][g][b] = true;
    }
}

inline void add (int &x, int y) {
    x = x + y;
    if (x >= MOD) {
        x -= MOD;
    }
}
inline void upd (int r, int g, int b) {
    if (dp[r][g][b]) {
        check(r, g, b);
        if (!dp[r][g][b]) {
            return;
        }
        int mx = max({r, g, b});
        add(dp[mx+1][g][b], dp[r][g][b]);
        add(dp[r][mx+1][b], dp[r][g][b]);
        add(dp[r][g][mx+1], dp[r][g][b]);
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, m) {
        int l, r, x;
        cin >> l >> r >> x;
        lim[r].emplace_back(l, x);
    }

    dp[0][0][0] = 1;
    upd(0, 0, 0);

    int ans = 0;
    REP1 (i, n) {
        REP (x, i) {
            REP (y, i) {
                if (x == 0 || y == 0 || x != y) {
                    upd(i, x, y);
                    upd(x, i, y);
                    upd(x, y, i);
                }
                if (i == n) {
                    add(ans, dp[i][x][y]);
                    add(ans, dp[x][i][y]);
                    add(ans, dp[x][y][i]);
                }
            }
        }

    }


    cout << ans << endl;
    return 0;
}


