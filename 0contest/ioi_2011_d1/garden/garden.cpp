#pragma GCC optimize("Ofast", "unroll-loops")
#pragma GCC target("avx", "avx2", "fma")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#define X first
#define Y second
#define eb emplace_back
#define pb push_back
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d-(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x) {cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y) {cerr<<x<<",";_do(y...);}
template<typename IT> ostream& printRng (ostream& os, IT bg, IT ed) {
    os << "{";
    for (IT it=bg; it!=ed; it++) {
        if (it == bg) os << *it;
        else os << "," << *it;
    }
    return os << "}";
}
template<typename T> ostream& operator << (ostream& os, const vector<T>& v) {return printRng(os,ALL(v));}
template<typename T, typename S> ostream& operator << (ostream& os, const pair<T,S>& v) {return os<<"("<<v.X<<","<<v.Y<<")";}
#else
#define debug(...)
#endif
#include "garden.h"
#include "gardenlib.h"

const int INF = 0x3f3f3f3f;
int n, m, p;
struct Edge {
    int to, w, id;
    bool operator < (const Edge &e) const {
        return w < e.w;
    }
};
vector<int> ed;
vector<vector<Edge>> edge;
vector<int> to, csz, dis, dfn, cdis, croot, cid, cpos;
vector<vector<int>> cycle;


int tme = 0;
int init;
void make_csz (int nd) {
    dfn[nd] = tme++;
    csz[nd] = INF;
    if (csz[to[nd]] == -1) make_csz(to[nd]);
    else if (csz[to[nd]] == INF) {
        if (dfn[to[nd]] >= init) {
            csz[to[nd]] = tme - dfn[to[nd]];
            int y = to[nd];
            vector<int> nc;
            for (int j=0; j<csz[to[nd]]; j++) {
                cpos[y] = SZ(nc);
                nc.eb(y);
                cdis[y] = 0;
                cid[y] = SZ(cycle);
                
                y = to[y];
            }
            cycle.eb(nc);
        }
    }
    csz[nd] = csz[to[nd]];
    if (cdis[nd] != 0) cdis[nd] = cdis[to[nd]] + 1;
}

void make_dis (int nd) {
    dis[nd] = INF;
    if (dis[to[nd]] == -1) make_dis(to[nd]);
    dis[nd] = dis[to[nd]] + 1;
}

vector<int> g, res, go;
vector<vector<int> > rev;

const int MAXN = 150000 * 2 + 5;
int chain[MAXN], ptr;
void make_tree (int nd, int par, int rt) {
    chain[ptr++] = nd;
    int sz = ptr;
    croot[nd] = rt;

    if (go[nd]) {
        for (int i=0; i<SZ(g); i++) {
            if (sz-1-g[i] >= 0) {
                res[i] += ed[chain[sz-1-g[i]]] == p;
            }
        }
    }

    for (int v : rev[nd]) {
        if (v != par && cdis[v] != 0) {
            make_tree(v, nd, rt);
        }
    }
    ptr--;
}

void count_routes(int N, int M, int P, int R[][2], int Q, int G[]) {
    edge.resize(N);
    n = N;
    m = M;
    p = P;

    for (int i=0; i<Q; i++) {
        g.eb(G[i]-1);
    }
    int cnt = 0;
    for (int i=0; i<M; i++) {
        int u = R[i][0], v = R[i][1];
        edge[u].pb({v, i, cnt++});
        edge[v].pb({u, i, cnt++});
    }
    ed.resize(cnt);
    rev.resize(cnt);
    for (int i=0; i<n; i++) {
        for (auto e : edge[i]) {
            ed[e.id] = e.to;
        }
    }
    to.resize(cnt), csz.resize(cnt, -1), dis.resize(cnt, -1);
    dfn.resize(cnt, 0);
    cdis.resize(cnt, -1);
    croot.resize(cnt), cid.resize(cnt), cpos.resize(cnt);
    for (int i=0; i<n; i++) {
        sort(ALL(edge[i]));
    }

    vector<int> start;
    go.resize(cnt);
    for (int i=0; i<n; i++) {
        for (const Edge &e : edge[i]) {
            int x = e.to;
            if (x == p) dis[e.id] = 0;
            if (SZ(edge[x]) == 1) {
                to[e.id] = edge[x][0].id;
            } else {
                to[e.id] = edge[x][edge[x][0].w == e.w ? 1 : 0].id;
            }
            rev[to[e.id]].eb(e.id);
        }
        start.eb(edge[i][0].id);
        go[edge[i][0].id] = true;
    }

    for (int i=0; i<cnt; i++) {
        if (csz[i] == -1) {
            init = tme;
            make_csz(i);
        }
    }
    debug(cdis, csz);
    for (int i=0; i<cnt; i++) {
        if (dis[i] == -1) {
            make_dis(i);
        }
    }

    res.resize(Q);
    debug(cycle, cdis);
    for (auto &v : cycle) {
        for (int r : v) {
            make_tree(r, -1, r);
        }
    }

    for (int i=0; i<n; i++) {
        if (dis[edge[i][0].id] >= INF) continue;
        for (int j=0; j<Q; j++) {
            int id = edge[i][0].id;
            int d = G[j] - 1;
            if (d > cdis[id]) {
                int rt = croot[id];
                int cp = cpos[rt];
                int tg = cycle[cid[rt]][(cp + d - cdis[id]) % csz[id]];
                res[j] += ed[tg] == p;
            }
        }
    }

    for (int _=0; _<Q; _++) {
        answer(res[_]);
    }
}


/*
6 5 2
1 3
0 1
1 2
3 4
3 5
5
32 4 2 1 23 
0 0 0 0 0
 */
