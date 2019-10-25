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

const int MAXN = 3003;
const ll MOD = 1000000007;

int n, m, dis[MAXN][MAXN];
vector<int> edg[MAXN];

bool vis[MAXN];

void build (int st) {
    queue<int> que;
    memset(vis, 0, sizeof(vis));
    que.emplace(st);
    vis[st] = true;

    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (auto v : edg[cur]) {
            if (!vis[v]) {
                vis[v] = true;
                dis[st][v] = dis[st][cur] + 1;
                que.emplace(v);
            }
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, m) {
        int u, v;
        cin >> u >> v;
        edg[u].emplace_back(v);
        edg[v].emplace_back(u);
    }

    REP1 (i, n) {
        build(i);
    }

    int s1, t1, l1, s2, t2, l2;
    cin >> s1 >> t1 >> l1;
    cin >> s2 >> t2 >> l2;

    debug(dis[4][3], dis[3][2], dis[2][1]);
    if (dis[s1][t1] > l1 || dis[s2][t2] > l2) {
        cout << -1 << endl;
    } else {
        int ans = dis[s1][t1] + dis[s2][t2];
        REP1 (i, n) {
            REP1 (j, n) {
                REP (k, 2) {
                    swap(s2, t2);
                    bool ac1 = (dis[i][s1] + dis[i][j] + dis[j][t1]) <= l1;
                    bool ac2 = (dis[i][t2] + dis[i][j] + dis[s2][j]) <= l2;

                    if (ac1 && ac2) {
                        int cur = dis[i][s1] + dis[i][j] + dis[j][t1] + dis[i][t2] + dis[s2][j];
                        debug(i, j, cur);
                        ans = min(ans, cur);
                    }
                }
            }
        }

        cout << m - ans << endl;
    }
}
