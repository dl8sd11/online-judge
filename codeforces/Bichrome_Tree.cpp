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

const int MAXN = 1003;
const int MAXC = 5003;
const int iNF = 0x3f3f3f3f;

int n, p[MAXN], x[MAXN], dp[MAXN][2];
vector<int> edg[MAXN];
int mn[2][MAXC];

void ckmin (int &cu, const int &va) {
    if (cu > va) {
        cu = va;
    }
}

void dfs (int nd) {
    for (auto v : edg[nd]) {
        dfs(v);
    }
    int sz = SZ(edg[nd]);

    memset(mn, iNF, sizeof(mn));
    mn[0][0] = 0;
    REP1 (i, sz) { // black
        int v = edg[nd][i-1];
        for (int j=0; j<MAXC; j++) {
            mn[i&1][j] = iNF;
            if (dp[v][0] != iNF && j >= x[v]) {
                ckmin(mn[i&1][j], mn[i&1^1][j-x[v]] + dp[v][0]);
            }
            if (dp[v][1] != iNF && j >= dp[v][1]) {
                ckmin(mn[i&1][j], mn[i&1^1][j-dp[v][1]] + x[v]);
            }
        }
    }

    dp[nd][0] = iNF;
    REP (i, x[nd]+1) {
        dp[nd][0] = min(dp[nd][0], mn[sz&1][i]);
    }


    memset(mn, iNF, sizeof(mn));
    mn[0][0] = 0;
    REP1 (i, sz) { // white
        int v = edg[nd][i-1];
        for (int j=0; j<MAXC; j++) {
            mn[i&1][j] = iNF;
            if (dp[v][1] != iNF && j >= x[v]) {
                ckmin(mn[i&1][j], mn[i&1^1][j-x[v]] + dp[v][1]);
            }
            if (dp[v][0] != iNF && j >= dp[v][0]) {
                ckmin(mn[i&1][j], mn[i&1^1][j-dp[v][0]] + x[v]);
            }
        }
    }

    dp[nd][1] = iNF;
    REP (i, x[nd]+1) {
        dp[nd][1] = min(dp[nd][1], mn[sz&1][i]);
    }
}

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    for (int i=2; i<=n; i++) {
        cin >> p[i];
        edg[p[i]].emplace_back(i);
    }

    REP1 (i, n) {
        cin >> x[i];
    }

    dfs(1);

    REP1 (i, n) {
        debug(dp[i][0], dp[i][1]);
    }

    cout << (min(dp[1][1], dp[1][0]) == iNF ? "IMPOSSIBLE" : "POSSIBLE") << endl;

}
