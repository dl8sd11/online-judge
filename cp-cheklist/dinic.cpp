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

const int MAXN = 2003;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, m, s, t;

struct Edge {
    int des;
    ll flow, cap;
    int nxt;
} edge[MAXN*5];
int lev[MAXN], head[MAXN], ecnt;


void add_edge (int f, int d, ll cap) {
    debug(f, d, cap);
    edge[ecnt++] = {d, 0, cap, head[f]};
    head[f] = ecnt-1;
    edge[ecnt++] = {f, 0, 0, head[d]};
    head[d] = ecnt-1;
}

ll dfs (int nd, ll lim) {
    if (nd == t || lim == 0) {
        return lim;
    }
    for (int i=head[nd]; i!=-1; i=edge[i].nxt) {
        int x = edge[i].des;
        if (lev[x] == lev[nd]+1 && edge[i].cap > edge[i].flow) {
            ll df = dfs(x, min(edge[i].cap-edge[i].flow, lim));
            if (df) {
                edge[i].flow += df;
                edge[i^1].flow -= df;
                return df;
            }
        }
    }
    return 0;
}

bool bfs () {
    queue<int> que;
    que.emplace(s);
    memset(lev, -1, sizeof(lev));
    lev[s] = 0;
    while (que.size()) {
        int cur = que.front();
        que.pop();

        for (int i=head[cur]; i!=-1; i=edge[i].nxt) {
            int x = edge[i].des;
            if (edge[i].flow < edge[i].cap && lev[x] == -1) {
                lev[x] = lev[cur] + 1;
                que.emplace(x);
            }
        }
    }

    return lev[t] != -1;
}

ll dinic () {
    ll flow = 0;
    while (bfs()) {
        ll df = 0;
        while (df=dfs(s, INF)) {
            flow += df;
        }
    }
    return flow;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    memset(head, -1, sizeof(head));
    cin >> n >> m;
    REP1 (i, n) {
        int a;
        cin >> a;
        add_edge(0, i, a);
    }

    ll sum = 0;
    REP1 (i, m) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, i+n, INF);
        add_edge(v, i+n, INF);
        add_edge(i+n , n+m+1, w);
        sum += w;
    }

    s = 0, t = n+m+1;
    cout << sum - dinic() << endl;

}
