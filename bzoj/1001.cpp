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

const ll MOD = 1000000007;
const int INF = 0x3f3f3f3f;

struct Dinic {
    struct Edge {
        int t, cap, flow, nxt;
    };
    vector<Edge> edge;
    vector<int> lev, cur, head;
    int N, F, T;

    Dinic (int n) : N(n), lev(n), cur(n), head(n, -1) {
        edge.reserve(3000000);
    }


    void add_edge (int f, int t, int cap) {
//        debug(f, t, cap);
        edge.push_back({t, cap, 0, head[f]});
        head[f] = SZ(edge) - 1;
        edge.push_back({f, 0, 0, head[t]});
        head[t] = SZ(edge) - 1;
    }


    bool bfs () {
        lev.assign(N, -1);
        queue<int> que;
        que.emplace(F);
        lev[F] = 0;
        while (que.size()) {
            int nd = que.front();
            que.pop();
//            debug(nd);

            for (int x=head[nd]; x!=-1; x=edge[x].nxt) {
                int t = edge[x].t;
                if (edge[x].cap > edge[x].flow && lev[t] == -1) {
                    lev[t] = lev[nd] + 1;
                    que.emplace(t);
                }
            }
        }

        return lev[T] != -1;
    }

    int dfs (int nd, int lim) {
        if (nd == T || lim == 0) {
            return lim;
        }
        for (int &x=cur[nd]; x!=-1; x=edge[x].nxt) {
            int t = edge[x].t;
            int rem = edge[x].cap - edge[x].flow;
            if (lev[t] == lev[nd] + 1 && rem > 0) {
                int df = dfs(t, min(lim, rem));
                if (df > 0) {
                    edge[x].flow += df;
                    edge[x^1].flow -= df;
                    return df;
                }
            }
        }
        return 0;
    }

    int max_flow (int f, int t) {
        int res = 0;
        F = f, T = t;
        while (bfs()) {
            int df = 0;
            REP (i, N) {
                cur[i] = head[i];
            }
            while (df = dfs(f, INF)) {
                res += df;
//                debug(df);
            }

        }
        return res;
    }
};

int n, m;

int id (int x, int y) {
    return x*m + y;
}

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    Dinic dinic(n*m);

    REP (i, n) {
        REP (j, m-1) {
            int w;
            cin >> w;
            dinic.add_edge(id(i,j), id(i,j+1), w);
            dinic.add_edge(id(i,j+1), id(i,j), w);
        }
    }

    REP (i, n-1) {
        REP (j, m) {
            int w;
            cin >> w;
            dinic.add_edge(id(i,j), id(i+1,j), w);
            dinic.add_edge(id(i+1,j), id(i,j), w);
        }
    }

    REP (i, n-1) {
        REP (j, m-1) {
            int w;
            cin >> w;
            dinic.add_edge(id(i,j), id(i+1,j+1), w);
            dinic.add_edge(id(i+1,j+1), id(i,j), w);
        }
    }

    cout << dinic.max_flow(0, id(n-1,m-1)) << endl;

}
/*
2 2
5
4
5 6
5
*/
