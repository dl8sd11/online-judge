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

const int MAXN = 102;
const ll MOD = 1000000007;
const int iNF = 0x3f3f3f3f;
/*
s = 0
row = [1, n]
col = [n+1, n+m]
t = n+m+1
*/

int n, m, head[MAXN*2], s, t;
struct Edge {
    int t, flow, cap, nxt;
} edge[MAXN * MAXN * 4];
int edge_cnt;

void add_edge (int f, int T, int cap) {
    edge[edge_cnt++] = {T, 0, cap, head[f]};
    head[f] = edge_cnt - 1;
    edge[edge_cnt++] = {f, 0, 0, head[T]};
    head[T] = edge_cnt - 1;
}

int lev[MAXN*2];
int dfs (int nd, int lim) {
    if (nd == t || lim == 0) {
        return lim;
    }

    for (int i=head[nd]; i!=-1; i=edge[i].nxt) {
        int x = edge[i].t;
        if (lev[x] == lev[nd]+1 && edge[i].cap > edge[i].flow) {
            int df = 0;
            if (df = dfs(x, min(lim, edge[i].cap - edge[i].flow))) {
                edge[i].flow += df;
                edge[i^1].flow -= df;
                return df;
            }
        }
    }

    return 0;
}

bool bfs () {
    memset(lev, -1, (n+m+2) * sizeof(int));
    lev[s] = true;
    queue<int> que;
    que.emplace(s);

    while (SZ(que)) {
        int cur = que.front();
        que.pop();

        for (int i=head[cur]; i!=-1; i=edge[i].nxt) {
            int x = edge[i].t;
            if (lev[x] == -1 && edge[i].cap > edge[i].flow) {
                lev[x] = lev[cur] + 1;
                que.emplace(x);
            }
        }
    }

    return lev[t] != -1;
}

int dinic (int x, int y) {
    s = x, t = y;
    int ret = 0;
    while (bfs()) {
        int df = 0;
        while (df = dfs(s, iNF)) {
            ret += df;
        }
    }
    return ret;
}

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    memset(head, -1, (n+m+2) * sizeof(int));

    REP1 (i, n) {
        REP1 (j, m) {
            char c;
            cin >> c;
            if (c == 'o') {
                add_edge(i, n+j, 1);
                add_edge(n+j, i, 1);
            } else if (c == 'S') {
                add_edge(0, i, iNF);
                add_edge(0, n+j, iNF);
            } else if (c == 'T') {
                add_edge(i, n+m+1, iNF);
                add_edge(n+j, n+m+1, iNF);
            } else {
                assert(c == '.');
            }
        }
    }

    int ans = dinic(0, n+m+1);
    cout << (ans >= iNF ? -1 : ans) << endl;

    return 0;
}
