#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
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
const int MAXN = 100005;

vector<pll> edge[MAXN];
int n, m;
pii p1, p2;

struct Dijkstra {
    int src;
    ll dis[MAXN];
    bool vis[MAXN];
    Dijkstra (int nd) : src(nd) {
        memset(dis, 0x3f, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        build();
    }

    void build () {
        priority_queue<pll,vector<pll>,greater<pll>> pq;
        pq.emplace(0, src);
        dis[src] = 0;

        while (pq.size()) {
            int cur = pq.top().Y;
            pq.pop();

            if (vis[cur]) {
                continue;
            }
            vis[cur] = true;

            for (auto p : edge[cur]) {
                if (dis[cur] + p.Y < dis[p.X]) {
                    dis[p.X] = dis[cur] + p.Y;
                    pq.emplace(dis[p.X], p.X);
                }
            }
        }
    }
};

ll mu[MAXN], mv[MAXN];
int main () {
    IOS();

    cin >> n >> m;
    cin >> p1.X >> p1.Y;
    cin >> p2.X >> p2.Y;


    for (int i=0; i<m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edge[u].eb(v, w);
        edge[v].eb(u, w);
    }

    Dijkstra ds(p1.X), dt(p1.Y), du(p2.X), dv(p2.Y);
    debug(ds.dis[p1.Y]);

    vector<pll> nid;
    nid.reserve(n);

    REP1 (i, n) {
        nid.emplace_back(ds.dis[i], i);
    }
    sort(ALL(nid));

    ll ans = du.dis[p2.Y];
    for (auto p : nid) {
        int nd = p.Y;

        mu[nd] = du.dis[nd];
        mv[nd] = dv.dis[nd];

        for (auto e : edge[nd]) {
            if (ds.dis[e.X] + e.Y == ds.dis[nd]) {
                mu[nd] = min(mu[nd], mu[e.X]);
                mv[nd] = min(mv[nd], mv[e.X]);
            }
        }

        if (ds.dis[p1.Y] == ds.dis[nd] + dt.dis[nd]) {
            ans = min(ans, dv.dis[nd] + mu[nd]);
            ans = min(ans, du.dis[nd] + mv[nd]);
        }

    }


    cout << ans << endl;

    return 0;
}
