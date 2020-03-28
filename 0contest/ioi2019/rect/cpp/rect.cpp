#include "rect.h"
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<short,short> pii;
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second

#define eb emplace_back
#define SZ(i) int(i.size())
#ifdef tmd
#define debug(...) fprintf(stderr,"%d (%s) = ",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do (T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do (T &&x, S &&...y) {cerr<<x<<",";_do(y...);}
template<typename IT> ostream &printRng (IT bg, IT ed, ostream &os) {
    os<<"{";
    for (IT it=bg; it!=ed; it++) {
        if (it!=bg) {
            os<<",";
        }
        os<<(*it);
    }
    return os<<"}";
}
template<typename T> ostream &operator << (ostream &os, vector<T> &vec) {
    return printRng(vec.begin(), vec.end(), os);
}
template<typename T> ostream &operator << (ostream &os, pair<T,T> &vec) {
    return os<<"{"<<vec.first<<","<<vec.second<<"}";
}
template<typename T> void pary (T bg, T ed) {
    printRng(bg,ed,cerr);
    cerr<<endl;
}
#else
#define debug(...)
#define pary(...)
#endif // tmd

const int MAXN = 2502;

int n, m;

int bit[MAXN];

void add (int x, int y) {
    for (x++;x<MAXN;x+=-x&x) {
        bit[x] += y;
    }
}

int sqry (int x) {
    int ret = 0;
    for (x++;x>0; x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

vector<vector<int> > G;

struct Edge {
    pii dt;
    int nxt;
} edge[MAXN*MAXN*2];
int h[MAXN][MAXN], g[MAXN][MAXN], cnt;

void addEdge (int x, int y, pii dt, int v[MAXN][MAXN]) {
    edge[cnt++] = {dt, v[x][y]};
    v[x][y] = cnt - 1;
}

struct Node {
    short x;
    int nxt;
} node[MAXN*MAXN*2];
int pa[MAXN][MAXN], ncnt;

void addNode (int x, int y, short dt, int v[MAXN][MAXN]) {
    node[ncnt++] = {dt, v[x][y]};
    v[x][y] = ncnt - 1;
}

int solve (int i, int j) {
    vector<pair<int,int> > qry, gg;
    for (int id=h[i][j]; id!=-1; id=edge[id].nxt) {
        qry.emplace_back(edge[id].dt);
        swap(qry.back().first, qry.back().second);
    }
    for (int id=g[j][i]; id!=-1; id=edge[id].nxt) {
        gg.emplace_back(edge[id].dt);
    }
    reverse(ALL(gg));

    sort(qry.begin(), qry.end());

    int res = 0;
    int idx = 0;

    vector<int> opr;
    int sum = 0;
    for (auto p : qry) {

        while (idx < int(gg.size()) && gg[idx].X <= p.X) {
            add(gg[idx].Y, 1);
            sum ++;
            opr.eb(gg[idx].Y);
            idx++;
        }

        res += sum - sqry(p.Y-1);
    }

    for (auto p : opr) {
        add(p, -1);
    }

    if (res) {
        debug(i, j, res);
        debug(qry);
        debug(gg);
    }

    return res;
}

void build (int res[MAXN][MAXN]) {
	memset(pa, -1, sizeof(pa));
    ncnt = 0;
    vector<int> stk;
    for (int i=0; i<n; i++) {
        stk.clear();
        for (int j=0; j<m; j++) {
            while (stk.size() && G[i][stk.back()] < G[i][j]) {
                if (stk.back() < j - 1) {
                    addNode(stk.back(),j,i,pa);
                    debug(stk.back(), j, i);
                }
                stk.pop_back();
            }
            if (stk.size()) {
                if (stk.back() < j - 1) {
                    debug(stk.back(), j, i);
                    addNode(stk.back(),j,i,pa);
                }
            }

            while (stk.size() && G[i][stk.back()] == G[i][j]) {
                stk.pop_back();
            }
            stk.eb(j);
        }
    }
//    debug("hf");

    for (int l=0; l<m; l++) {
        for (int r=l+2; r<m; r++) {
            int len = 0;

            int ls = -1;
            for (int k=pa[l][r]; k!=-1; k=node[k].nxt) {
                int x = node[k].x;
                if (ls!=-1 && x+1!=ls) {
                    len = 0;
                }
                len++;
                addEdge(x-1,l,{r-l-1, len},res);
                ls = x;
            }
        }
    }
}


vector<vector<int> > flip (vector<vector<int> > vec) {
    vector<vector<int> > res;
    for (int j=0; j<SZ(vec[0]); j++) {
        vector<int> cur;
        for (int i=0; i<SZ(vec); i++) {
            cur.emplace_back(vec[i][j]);
        }
        res.emplace_back(cur);
    }
    swap(n, m);
    return res;
}

long long count_rectangles(std::vector<std::vector<int> > a) {
    G = a;
	n = a.size();
	m = a[0].size();
	debug(n, m);

	memset(h, -1, sizeof(h));
	memset(g, -1, sizeof(g));

	build(h);
	G = flip(G);
	debug("FL");
	build(g);
	G = flip(G);

    ll res = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            res += solve(i, j);
        }
    }
    return res;
}
