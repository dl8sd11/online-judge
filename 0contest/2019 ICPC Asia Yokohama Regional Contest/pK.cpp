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

const int MAXN = 41;
const int MAXD = 4*MAXN*MAXN + 11;
const ll MOD = 1000000007;
const int INF = 0x3f3f3f3f;

int n, m, a, b, c, s, t;
bool blk;

int id (int x, int y) { // bh, !bv, !wh wv
    return (x * m + y) * 4;
}

struct Edge {
    int t, cap, flow, nxt;
} edge[50*MAXD];
int cnt, cur[MAXD], head[MAXD], lev[MAXD];

void add_edge (int F, int T, int C) {
//    debug(F, T, C);
    edge[cnt] = {T, C, 0, head[F]};
    head[F] = cnt++;
    edge[cnt] = {F, 0, 0, head[T]};
    head[T] = cnt++;
}

int dfs (int nd ,int lim) {
    if (nd == t || lim == 0) {
        return lim;
    }
    for (int &it=cur[nd]; it!=-1; it=edge[it].nxt) {
        int u = edge[it].t;
        int rem = edge[it].cap - edge[it].flow;

        if (lev[u] == lev[nd] + 1 && rem > 0) {
            int df;
            if (df = dfs(u, min(lim, rem))) {
                edge[it].flow += df;
                edge[it^1].flow -= df;
                return df;
            }
        }
    }
    return 0;
}


bool bfs () {
    vector<int> que;
    memset(lev, -1, sizeof(lev));
    lev[s] = 0;
    que.eb(s);

    while (que.size()) {
        int nd = que.back();
        que.pop_back();

        for (int it=head[nd]; it!=-1; it=edge[it].nxt) {
            int u = edge[it].t;
            if (lev[u] == -1 && edge[it].cap > edge[it].flow) {
                lev[u] = lev[nd] + 1;
                que.eb(u);
            }
        }
    }

    return lev[t] != -1;
}

int Dinic () {
    int flow = 0;
    while (bfs()) {
        REP (i, t+1) {
            cur[i] = head[i];
        }
        int df = 0;
        while (df = dfs(s, INF)) {
            flow += df;
        }
    }
    return flow;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m >> a >> b >> c;
    memset(head, -1, sizeof(head));

    s = id(n-1,m-1) + 4, t = id(n-1,m-1) + 5;
    REP (x, n) {
        REP (y, m) {
            char ch;
            #ifdef tmd
            blk = rand() % 2;
            #else
            cin >> ch;
            blk = ch == '#';
            #endif // tmd

            int bh = id(x, y);
            int nbv = id(x, y) + 1;
            int nwh = id(x, y) + 2;
            int wv = id(x, y) + 3;

            if (x > 0) {
                add_edge(bh, id(x-1,y), b);
                add_edge(id(x-1,y)+2, nwh, b);
            } else {
                add_edge(bh, t, b);
                add_edge(s, nwh, b);
            }

            if (y > 0) {
                add_edge(wv, id(x,y-1)+3, b);
                add_edge(id(x,y-1)+1, nbv, b);
            }  else {
                add_edge(wv, t, b);
                add_edge(s, nbv, b);
            }

            add_edge(bh, t, a);
            add_edge(wv, t, a);
            add_edge(s, nbv, a);
            add_edge(s, nwh, a);

            if (blk) {
                add_edge(wv, t, INF);
                add_edge(s, nwh, INF);
                add_edge(nbv, bh, c);
            } else {
                add_edge(bh, wv, c);
                add_edge(nwh, nbv, c);
                add_edge(bh, nbv, INF);
            }
        }
    }
    debug("built");

    cout << Dinic() << endl;
}
/*
1 1 1 1 1
#
*/
