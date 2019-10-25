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

const int MAXN = 100005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n;
ll dp[MAXN][4][4];
ll c[MAXN][4];
int ans[MAXN], tran[MAXN][4][4];

vector<int> edg[MAXN], chain;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP1 (cl, 3) {
        REP1 (i, n) {
            cin >> c[i][cl];
        }
    }

    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        edg[u].emplace_back(v);
        edg[v].emplace_back(u);
    }

    int root = -1;
    REP1 (i, n) {
        if (SZ(edg[i]) == 1) {
            root = i;
        } else if (SZ(edg[i]) >= 3) {
            cout << -1 << endl;
            return 0;
        }
    }

    int lst = -1;
    chain.emplace_back(-1);
    REP (i, n) {
        chain.emplace_back(root);
        for (auto v : edg[root]) {
            if (v != lst) {
                lst = root;
                root = v;
                break;
            }
        }
    }

    #ifdef tmd
    for (auto v : chain) {
        debug(v);
    }
    #endif

    REP1 (i, 3) {
        REP1 (j, 3) {
            dp[2][i][j] = (i == j ? INF : c[chain[1]][i] + c[chain[2]][j]);
        }
    }
    debug(dp[2][2][3]);

    for (int i=3; i<=n; i++) {
        int X =chain[i];
        debug(X);
        REP1 (y, 3) {
            REP1 (z, 3) {
                dp[i][y][z] = INF;
                REP1 (x, 3) {
                    if (x != y && y != z && x != z) {
                        if (dp[i-1][x][y] + c[X][z] < dp[i][y][z]) {
                            dp[i][y][z] = dp[i-1][x][y] + c[X][z];
                            tran[i][y][z] = x;
                        }
                    }
                }
            }
        }
    }

    pair<int,int> bk;
    ll mn = INF;

    REP1 (x, 3) {
        REP1 (y, 3) {
            if (dp[n][x][y] < mn) {
                mn = dp[n][x][y];
                bk = {x, y};
            }
        }
    }

    REP (i, n-2) {
        ans[chain[n-i]] = bk.second;
        bk = {tran[n-i][bk.first][bk.second], bk.first};
    }
    ans[chain[2]] = bk.second;
    ans[chain[1]] = bk.first;

    cout << mn << endl;
    REP1 (i, n) {
        cout << ans[i] << " \n"[i==n];
    }


    return 0;
}
