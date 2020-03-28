#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
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
const int MAXN = 302;

ll dis[MAXN][MAXN];
int n, m;
pii p1, p2;

int main () {
    IOS();

    cin >> n >> m;
    cin >> p1.X >> p1.Y;
    cin >> p2.X >> p2.Y;


    memset(dis, 0x3f, sizeof(dis));
    for (int i=0; i<m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dis[u][v] = dis[v][u] = w;
    }

    for (int i=1; i<=n; i++) {
        dis[i][i] = 0;
    }

    for (int k=1; k<=n; k++) {
        for (int u=1; u<=n; u++) {
            for (int v=1; v<=n; v++) {
                if (dis[u][k] != INF && dis[k][v] != INF && dis[u][k]+dis[k][v] < dis[u][v]) {
                    dis[u][v] = dis[u][k] + dis[k][v];
                }
            }
        }
    }

    ll ans = dis[p2.X][p2.Y];

    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {

            ll mn = dis[p1.X][i] + dis[i][j] + dis[j][p1.Y];
            mn = min(mn, dis[p1.X][j] + dis[i][j] + dis[i][p1.Y]);

            if (mn == dis[p1.X][p1.Y]) {
                if (i == 2 && j == 1) {
                    debug(dis[p1.X][i] + dis[i][j] + dis[j][p1.Y]);
                    debug(dis[p2.X][i], dis[j][p2.Y]);
                }
                ans = min(ans, dis[p2.X][i] + dis[j][p2.Y]);
            }
        }
    }


    cout << ans << endl;

    return 0;
}
