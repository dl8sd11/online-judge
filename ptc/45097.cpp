#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
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

const int MAXN = 11;
const ll MOD = 1000000007;
const int INF = 0x3f3f3f3f;

int h, w;
bool a[MAXN][MAXN];

struct Edge {
    int t, cap, flow, nxt;
} edge[MAXN*MAXN*11];

int ecnt;
int head[MAXN*MAXN];

int S, T;

void addEdge (int f, int t, int c) {
    if (c==0)return;
    if (f == S) {
        debug(f, t, c, "start");
    }
    if (t == T) {
        debug(f, t, c, "END");
    }
    debug(f,t,c);

    edge[ecnt++] = (Edge){t, c, 0, head[f]};
    head[f] = ecnt - 1;
    edge[ecnt++] = (Edge){f, 0, 0, head[t]};
    head[t] = ecnt - 1;
}

int lev[MAXN*MAXN];

int dfs (int nd, int lim) {
    if (nd == T || lim == 0) {
        return lim;
    }
    for (int id=head[nd]; id!=-1; id=edge[id].nxt) {
        int x = edge[id].t;
        int rem = edge[id].cap - edge[id].flow;

        if (lev[nd] == lev[x] - 1 && rem > 0) {
            int df;

            if (df = dfs(x, min(lim,rem))) {
                edge[id].flow += df;
                edge[id^1].flow -=df;
                return df;
            }

        }
    }

    return 0;
}

bool bfs () {
    queue<int> que;
    memset(lev, -1,sizeof(lev));
    lev[S] = 0;
    que.emplace(S);

    while (que.size()) {
        int cur = que.front();
        que.pop();

        for (int id=head[cur];id!=-1;id=edge[id].nxt) {
            int x = edge[id].t;
            if (lev[x] == -1 && edge[id].cap > edge[id].flow) {
                lev[x] = lev[cur] + 1;
                que.emplace(x);
            }
        }

    }

    return lev[T] != -1;
}

int minCut () {
    int flow = 0;
    while (bfs()) {
        int df;
        while (df = dfs(S, INF)) {
            flow += df;
            debug(df, flow);
        }
    }
    return flow;
}

void init() {
    ecnt = 0;
    memset(head, -1, sizeof(head));
}

int toID (int x, int y) {
    return x * w + y + 1;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    while (cin >> h >> w && w*h != 0) {
        S = 0;
        T = 1;

        init();
        REP (i, h) {
            REP (j, w) {
                cin >> a[i][j];
                int id = toID(i, j);
                if (a[i][j]) {
                    addEdge(S, id*2, 1);
                    addEdge(id*2, id*2+1, INF);
                    addEdge(id*2+1, T, 3);
                } else {
                    addEdge(S, id*2, 3);
                    addEdge(id*2, id*2+1, INF);
                    addEdge(id*2+1, T, 1);
                }

                if (i) {
                    int id2 = toID(i-1, j);
                    addEdge(id*2, id2*2+1, 1);
                    addEdge(id2*2, id*2+1, 1);
                }

                if (j) {
                    int id2 = toID(i, j-1);
                    addEdge(id*2, id2*2+1, 1);
                    addEdge(id2*2, id*2+1, 1);
                }
            }
        }

        debug("built");
        cout << minCut() -h*w << endl;
    }
}
/*
3 3
1 1 0
1 1 0
1 0 0
3 3
1 0 1
0 1 0
1 0 1
*/
