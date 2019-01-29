#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
const ll MAXN = 53;
ll dp[MAXN][MAXN],n,m;
bool vis[3000];

void build() {
    REP1 (i,n) {
        REP1 (j,m) {
            memset(vis,0,sizeof(vis));
            vis[0] = 1;
            REP (a,i) {
                REP (b,j) {
                    vis[dp[a][b] ^ dp[a][j] ^ dp[i][b]] = true;
                }
            }
            REP (k,3000) {
                if (!vis[k]) {
                    dp[i][j] = k;
                    break;
                }
            }
        }
    }
}
bool bi[MAXN][MAXN];
int main () {
    freopen("coins.in ","r",stdin);
    freopen("coins.out ","w",stdout);
    cin >> n >> m;
    build();
    ll ans = 0;
    REP1 (i,n) {
        REP1 (j,m) {
            char c;
            cin >> c;
            bi[i][j] = (c == '1');
            ans ^= dp[i][j] * bi[i][j];
        }
    }

    if (ans == 0) {
        cout << "Betty" << endl;
    } else {
        cout << "Ann" << endl;
        REP1 (i,n) {
            REP1 (j,m) {
                REP (a,i) {
                    REP (b,j) {
                        if (bi[i][j]) {
                            if ((ans ^ dp[a][b] ^ dp[i][j] ^ dp[a][j] ^ dp[i][b] )== 0) {
                                cout << i << " " << j << endl;
                                cout << a << " " << b << endl;
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
}