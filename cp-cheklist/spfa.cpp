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

const int MAXN = 1000006;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, e, s, t;

ll dis[MAXN];
bool inq[MAXN];
vector<pair<int,int> > edge[MAXN];

void add_edge (int u, int v, int w) {
    edge[u].emplace_back(v, w);
}

ll spfa () {
    queue<int> que;
    que.emplace(s);
    memset(dis, INF, sizeof(dis));
    dis[s] = 0;
    inq[s] = true;

    while (que.size()) {
        int cur = que.front();
        que.pop();
        inq[cur] = false;

        for (auto p : edge[cur]) {
            if (dis[p.first] > dis[cur] + p.second) {
                dis[p.first] = dis[cur] + p.second;
                if (!inq[p.first]) {
                    que.emplace(p.first);
                    inq[p.first] = true;
                }
            }
        }
    }

    return dis[t] == INF ? -1 : dis[t];
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> e >> s >> t;
    REP (i, e) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
    }

    cout << spfa() << endl;
}
