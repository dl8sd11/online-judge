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
const ll INF = 0x3f3f3f3f3f3f3f3f;
typedef pair<int, int> pii;

int n, m;

struct Edge {
    int u, v, c;
    Edge (int i1, int i2, int i3) : u(i1), v(i2), c(i3){};
};
vector<Edge> org;
vector<int> edg[MAXN];
vector<int> rev[MAXN];
bool is_tree[MAXN];
bool on_path[MAXN];
ll fdi[MAXN], rdi[MAXN];

struct PQ {
    int nd, id;
    ll w;
    PQ (int v, int idd, ll c) : nd(v), id(idd), w(c){}
    bool operator < (const PQ &p) const {
        return w > p.w;
    }
};
bool vis[MAXN];
void dijkstra (ll *dis, vector<int> edge[], int src) {
    memset(dis, 0x3f3f3f3f, sizeof(ll)*MAXN);
    memset(vis, 0, sizeof(bool)*MAXN);
    memset(is_tree, 0, sizeof(bool)*MAXN);
    dis[src] = 0;
    priority_queue<PQ> pq;
    pq.emplace(src, MAXN-1, 0);

    while (pq.size()) {
        PQ cur = pq.top();
        pq.pop();
        if (vis[cur.nd]) {
            continue;
        }
        debug(cur.nd, cur.w);
        vis[cur.nd] = true;
        is_tree[cur.id] = true;

        for (int eid : edge[cur.nd]) {
            int t = org[eid].u ^ org[eid].v ^ cur.nd;
            if (dis[t] > dis[cur.nd] + org[eid].c) {
                dis[t] = dis[cur.nd] + org[eid].c;
                pq.emplace(t, eid, dis[t]);
            }
        }
    }
}

vector<int> path;
bool path_edge[MAXN];
void revisit (int src) {
    while (src != 1) {
        int cnt = 0, prv = -1, id = -1;
        for (auto eid : rev[src]) {
            if (is_tree[eid]) {
                cnt++;
                prv = org[eid].u;
                id = eid;
                path_edge[id] = true;
            }
        }
        path.emplace_back(id);
        assert(cnt == 1);
        on_path[src] = true;
        src = prv;
    }
    reverse(path.begin(), path.end());
    on_path[1] = true;
}

int path_anc[MAXN];
void dfs (int nd, int cur) {
    path_anc[nd] = cur;
    for (auto eid : edg[nd]) {
        if (is_tree[eid]) {
            if (path_edge[eid]) {
                dfs(org[eid].v, org[eid].v);
            } else {
                dfs(org[eid].v, cur);
            }
        }
    }
}

vector<int> alt[MAXN];
bool n_sad[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;

    REP (i, m) {
        int a, b, c;
        cin >> a >> b >> c;
        org.emplace_back(a, b, c);
        edg[a].emplace_back(i);
        rev[b].emplace_back(i);
    }

    dijkstra(rdi, rev, 2);
    dijkstra(fdi, edg, 1);
    revisit(2);
    dfs(1, 1);
    ll bs = fdi[2];
    debug(path_anc[5]);
    REP (i, m) {
        if (!is_tree[i] && on_path[org[i].v]) {
            if (fdi[org[i].u] + rdi[org[i].v] + org[i].c == bs) {
                int f = path_anc[org[i].u];
                alt[f].emplace_back(org[i].v);
                debug(f, org[i].v);
                debug(org[i].u, org[i].v);
            }
        }
    }

    int s = 1;
    set<int> ep;
    for (auto e : path) {
        ep.erase(s);
        int t = org[e].u ^ org[e].v ^ s;
        for (auto p : alt[s]) {
            ep.insert(p);
        }
        if (SZ(ep)) {
            n_sad[e] = true;
        }
        s = t;
    }

    REP (i, m) {
        ll cur = rdi[org[i].u] + fdi[org[i].v] + org[i].c;

        if (cur < bs) {
            cout << "HAPPY" << endl;
        } else if (n_sad[i] || (!path_edge[i]) || cur == bs){
            cout << "SOSO" << endl;
        } else {
            cout << "SAD" << endl;
        }
    }

    return 0;
}

/*
6 7
1 3 2
3 4 4
4 5 3
5 2 5
4 2 8
1 6 1
6 3 1

*/
