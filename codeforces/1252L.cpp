#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#ifdef tmdd
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

const int MAXN = 4005;
const ll MOD = 1000000007;
const int INF = 0x3f3f3f3f;

int n, k;
int par[MAXN];

struct Edge {
    int t, cap, flow, nxt;
} edge[100005];
int head[MAXN], ecnt;
int S, T;
void init () {
    memset(head, -1, sizeof(head));
}

void addEdge (int f, int t, int cap) {
    debug(f, t, cap);
    edge[ecnt++] = (Edge){t, cap, 0, head[f]};
    head[f] = ecnt - 1;
    edge[ecnt++] = (Edge){f, 0, 0, head[t]};
    head[t] = ecnt - 1;
}

int lev[MAXN], curID[MAXN];
int dfs (int nd, int lim) {
    if (nd == T || lim == 0) {
        return lim;
    }
    for (int &it=curID[nd];it!=-1;it=edge[it].nxt) {
        int x = edge[it].t;
        int rem = edge[it].cap - edge[it].flow;
        if (lev[x] == lev[nd] + 1 && rem > 0) {
            int df = dfs(x, min(lim, rem));
            if (df > 0) {
                edge[it].flow += df;
                edge[it^1].flow -= df;
                return df;
            }
        }
    }
    return 0;
}

bool bfs () {
    memset(lev, -1, sizeof(lev));
    queue<int> que;
    que.emplace(S);
    lev[S] = 0;

    while (!que.empty()) {
        int cur = que.front();
        que.pop();
        for (int it=head[cur];it!=-1;it=edge[it].nxt) {
            int x = edge[it].t;
            if (edge[it].cap > edge[it].flow && lev[x] == -1) {
                lev[x] = lev[cur] + 1;
                que.emplace(x);
            }
        }
    }

    return lev[T] != -1;
}

int dinic () {
    int flow = 0;
    while (bfs()) {
        int df = 0;
        for (int i=S;i<=T;i++) {
            curID[i] = head[i];
        }
        while (df = dfs(S, INF)) {
            flow += df;
        }
    }
    return flow;
}

int djs[MAXN];

int fnd (int nd) {
    return nd == djs[nd] ? nd : djs[nd] = fnd(djs[nd]);
}

bool mrg (int x, int y) {
    x = fnd(x), y = fnd(y);
    if (x == y) {
        return false;
    }
    djs[x] = y;
    return true;
}

map<int,int> ccnt;
map<int,int> cid;
vector<int> color;
vector<int> worker;

vector<int> mat[MAXN];
int deg[MAXN];

bool ncycle[MAXN];

const int C = 10;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;

    REP1 (i, n) {
        djs[i] = i;
    }
    init();

    int cnt = 0;
    REP1 (i, n) {
        #ifdef tmd
        par[i] = i%n+1;
        #else
        cin >> par[i];
        #endif // tmd
        cnt += mrg(i, par[i]);
        deg[par[i]]++;
        int m;
        #ifdef  tmd
        m = 5;
        #else
        cin >> m;
        #endif
        REP (j, m) {
            int d;
            #ifdef tmd
            d = rand() % C;
            #else
            cin >> d;
            #endif // tmd
            mat[i].emplace_back(d);
        }
    }

    REP (i, k) {
        int d;
        #ifdef tmd
        d = rand() % C;
        #else
        cin >> d;
        #endif // tmd
        ccnt[d]++;
        worker.emplace_back(d);
    }

    int csz = 0;
    for (auto p : ccnt) {
        cid[p.first] = csz++;
        color.emplace_back(p.first);
    }

    if (cnt != n-1) {
        debug(cnt);
        cout << -1 << endl;
        return 0;
    }

    queue<int> que;
    REP1 (i, n) {
        if (deg[i] == 0) {
            que.emplace(i);
        }
    }

    int ncnt = 0;
    while (que.size()) {
        int cur = que.front();
        que.pop();

        ncycle[cur] = true;
        ncnt++;

        if (--deg[par[cur]] == 0) {
            que.emplace(par[cur]);
        }
    }

    S = 0, T = 2 + n + csz;

    addEdge(S, 1, n-ncnt-1);
    REP1 (i, n) {
        debug(i, ncycle[i]);
        if (ncycle[i]) {
            addEdge(S, i+1, 1);
        } else {
            addEdge(1, i+1, 1);
        }
        for (auto d : mat[i]) {
            if (cid.count(d)) {
                addEdge(i+1, 2+n+cid[d], 1);
            }
        }
    }

    REP (i, csz) {
        addEdge(2+n+i, T, ccnt[color[i]]);
    }

    int match = dinic();
    debug(match);
    if (match < n-1) {
        cout << -1 << endl;
        return 0;
    }

    for (auto c : worker) {
        int id = cid[c];
        int nid = id+2+n;

        bool opt = false;
        while (head[nid]!=-1) {
            if (edge[head[nid]].flow == -1) {
                int x = edge[head[nid]].t - 1;
                cout << x << " " << par[x] << endl;
                opt = true;
                head[nid] = edge[head[nid]].nxt;
                break;
            }
            head[nid] = edge[head[nid]].nxt;
        }

        if (!opt) {
            cout << 0 << " " << 0 << endl;
        }
    }
}

