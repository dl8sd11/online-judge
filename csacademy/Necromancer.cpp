#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 1036;
const int INF = 0x3f3f3f3f;

int n, k, win;
vector<vector<int> > ctz;
bool vis[MAXN];


struct Edge {
    int t, cap, flow, nxt;
} edge[MAXN*MAXN];
int head[MAXN*2], cptr[MAXN*2];
int ecnt;

int F, T;

void add_edge (int f, int t, int cap) {
    edge[ecnt] = {t, cap, 0, head[f]};
    head[f] = ecnt++;
    edge[ecnt] = {f, 0, 0, head[t]};
    head[t] = ecnt++;
}

void init () {
    ecnt = 0;
    memset(head, -1, sizeof(head));
}

void build_graph (int lim) {
    init();
    F = SZ(ctz) + k;
    T = F + 1;

    REP (i, SZ(ctz)) {
        add_edge(F, i, 1);
        for (auto v : ctz[i]) {
            add_edge(i, SZ(ctz) + v - 1, 1);
        }
    }
    REP (i, k) {
        add_edge(SZ(ctz)+i, T, lim);
    }
}

int lev[MAXN*2];

int dfs (int nd, int lim) {
    if (nd == T || lim == 0) {
        return lim;
    }
    for (int &i=cptr[nd]; i!=-1; i=edge[i].nxt) {
        int x = edge[i].t;
        int rem = edge[i].cap - edge[i].flow;

        if (lev[x] == lev[nd] + 1 && rem > 0) {
            int df = dfs(x, min(lim, rem));
            if (df > 0) {
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
    que.emplace(F);
    memset(lev, -1, sizeof(lev));
    lev[F] = 0;

    while (que.size()) {
        int nd = que.front();
        que.pop();

        for (int i=head[nd]; i!=-1; i=edge[i].nxt) {
            int x = edge[i].t;

            if (lev[x] == -1 && edge[i].cap > edge[i].flow) {
                lev[x] = lev[nd] + 1;
                que.emplace(x);
            }
        }
    }
    return lev[T] != -1;
}

int dinic () {
    int flow = 0;
    while (bfs()) {
        int df;
        REP (i, T+1) {
            cptr[i] = head[i];
        }
        while (df = dfs(F, INF)) {
            flow += df;
        }
    }
    return flow;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;

    REP (i, n) {
        int sz, d, f;
        cin >> sz;

        memset(vis, 0, k+1);
        cin >> f;

        REP (j, sz-1) {
            cin >> d;
            vis[d] = true;
        }

        if (f == 1 || !vis[1]) {
            win++;
        } else {
            vector<int> cur;
            REP1 (j, k) {
                if (!vis[j]) {
                    cur.eb(j);
                }
            }
            ctz.eb(cur);
        }
    }

    int L = 0, R = SZ(ctz);
    while (L < R - 1) {
        int M = (L + R) >> 1;

        build_graph(M);
        if (dinic() == SZ(ctz)) {
            R = M;
        } else {
            L = M;
        }
    }
    debug(L, R, win);

    cout << max(0, R + 1 - win) << endl;
}
