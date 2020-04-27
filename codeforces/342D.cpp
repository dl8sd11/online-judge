#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define X first
#define Y second
const int MAXN = 10004;
const ll MOD = 1000000007;


void add (int &x, int y) {
    x = x + y >= MOD ? x + y - MOD : x + y;
}

int n;
struct Domino {
    bool ban[MAXN][3];
    ll res;
    int dp[2][16];

    Domino (vector<pii> b) {
        memset(ban, 0, sizeof(ban));
        for (auto p : b) {
            ban[p.X][p.Y] = true;
        } 
        solve();
    }
    void solve () {

        int fl = 1<<4;
        memset(dp, 0, sizeof(dp));
        dp[1][fl-1] = 1;

        bool roll = 1;
        for (int i=0; i<n; i++) {
            roll ^= 1;
            for (int st=0; st<fl; st++) {
                dp[roll][st] = 0;
            }
            
            for (int st=0; st<fl; st++) {
                add(dp[roll][(st<<1|1) & (fl-1)], dp[roll^1][st]);
            }
            for (int j=0; j<3; j++) {
                roll ^= 1;
                for (int st=0; st<fl; st++) {
                    dp[roll][st] = 0;
                }


                for (int st=0; st<fl; st++) {
                    int ul = (st>>j) & 3;
                    if (ul == 0) {
                        if (!ban[i][j] ) {
                            add(dp[roll][st|(3<<j)], dp[roll^1][st]);
                        }
                    } else if (ul == 1) { // L
                        if (!ban[i][j]) {
                            add(dp[roll][st|(3<<j)], dp[roll^1][st]);
                        }
                    } else if (ul == 2) { // U
                        if (ban[i][j]) {
                            add(dp[roll][st|(3<<j)], dp[roll^1][st]);
                        } else {
                            add(dp[roll][st^(2<<j)], dp[roll^1][st]);
                            if (j) {
                                add(dp[roll][st|(7<<(j-1))], dp[roll^1][st]);
                            }
                        }
                    } else { // both
                        if (ban[i][j]) {
                            add(dp[roll][st], dp[roll^1][st]);
                        } else {
                            add(dp[roll][st^(3<<j)], dp[roll^1][st]);
                        }
                    }
                }

            }
        }

        res = dp[roll][fl-1];
    }
};

vector<vector<pii> > vset;
vector<pii> oban;

char ch[MAXN][3];

pii cen;

ll ans;
void dfs (int id, int cnt, vector<pii> ban) {
    if (id == int(vset.size())) {
        if (cnt == 0) {
            return;
        }
        Domino dom(ban);
        ans += (cnt & 1 ? 1 : -1) * dom.res % MOD;
        ans %= MOD;
        if (ans < 0) {
            ans += MOD;
        }
    } else {
        dfs(id+1, cnt, ban);
        for (auto v : vset[id]) {
            ban.emplace_back(v);
        }
        dfs(id+1, cnt+1, ban);
    }
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int j=0; j<3; j++) {
        for (int i=0; i<n; i++) {
            cin >> ch[i][j];
            if (ch[i][j] == 'O') {
                cen = {i, j};
            } else if (ch[i][j] == 'X') {
                oban.emplace_back(i, j);
            }
        }
    }

    if (cen.X >= 2 && ch[cen.X-1][cen.Y] == '.' && ch[cen.X-2][cen.Y] == '.') {
        vset.push_back({pii(cen.X-1, cen.Y), pii(cen.X-2,cen.Y)});
    }
    if (cen.X < n-2 && ch[cen.X+1][cen.Y] == '.' && ch[cen.X+2][cen.Y] == '.') {
        vset.push_back({pii(cen.X+1, cen.Y), pii(cen.X+2,cen.Y)});
    }
    if (cen.Y == 0 && ch[cen.X][1] == '.' && ch[cen.X][2] == '.') {
        vset.push_back({pii(cen.X, 1), pii(cen.X,2)});
    }
    if (cen.Y == 2 && ch[cen.X][1] == '.' && ch[cen.X][0] == '.') {
        vset.push_back({pii(cen.X, 1), pii(cen.X,0)});
    }

    oban.emplace_back(cen);
    dfs(0, 0, oban);

    cout << ans << endl;

    return 0;
}
