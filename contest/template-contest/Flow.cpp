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

const int MAXN = 202;
const ll MOD = 1000000007;
const int INF = 0x3f3f3f3f;

int ts;
int n;

struct Edge {
    int t, cap, flow, nxt;
} edge[MAXN*MAXN*5];
int head[MAXN], ecnt;

void addEdge (int f, int t, int cap) {
    edge[ecnt++] = (Edge){t, cap, 0, head[f]};
    head[f] = ecnt - 1;
    edge[ecnt++] = (Edge){f, 0, 0, head[t]};
    head[t] = ecnt - 1;
}

void init () {
    memset(head, -1, sizeof(head));
    ecnt = 0;
}

int S, T;
void buildEdge (int f, int t) {
    if (f == S || t == T) {
        addEdge(f, t, 1);
    } else {
        addEdge(f, t, INF);
    }
}

int lev[MAXN], cur[MAXN];

int dfs (int nd, int lim) {
    if (nd == T || lim == 0) {
        return lim;
    }
    for (int &id=cur[nd];id!=-1;id=edge[id].nxt) {
        int x = edge[id].t;
        int rem = edge[id].cap - edge[id].flow;
        if (lev[x] == lev[nd] + 1 && rem > 0) {
            int df = dfs(x, min(lim, rem));
            if (df > 0) {
                edge[id].flow += df;
                edge[id^1].flow -= df;
                return df;
            }
        }
    }

    return 0;
}

bool bfs () {
    memset(lev, -1, sizeof(lev));
    lev[S] = 0;
    queue<int> que;
    que.emplace(S);

    while (que.size()) {
        int nd = que.front();
        que.pop();

        for (int id=head[nd];id!=-1;id=edge[id].nxt) {
            int x = edge[id].t;
            if (lev[x] == -1 && edge[id].cap > edge[id].flow) {
                que.emplace(x);
                lev[x] = lev[nd] + 1;
            }

        }

    }

    return lev[T] != -1;
}

int Dinic () {
    int flow = 0;
    while (bfs()) {
        int df = 0;
        debug(df);
        REP (i, T+1) {
            cur[i] = head[i];
        }
        while (df = dfs(S, INF)) {
            flow += df;
        }
    }
    return flow;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> ts;
    while (ts--) {
        init();

        cin >> n;
        S = 1, T = n;
        REP1 (i, n-1) {
            int m;
            cin >> m;
            REP (j, m) {
                int d;
                cin >> d;
                buildEdge(i, d);
            }
        }

        cout << Dinic() << endl;
    }
}
