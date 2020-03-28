#include "split.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define eb emplace_back
#define SZ(i) int(i.size())
#define X first
#define Y second

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
#else
#define debug(...)
#endif // tmd

const int MAXN = 100005;
const int MAXM = 200005;

vector<int> edge[MAXN], tree[MAXN], btree[MAXN];
vector<pair<int,int> > gp;

bool vis[MAXN];
int sz[MAXN];

int N;

pair<int,int> msplit = {1, MAXN+1};

void span (int nd) {
    vis[nd] = true;
    sz[nd] = 1;
    for (auto v : edge[nd]) {
        if (!vis[v]) {
            span(v);
            sz[nd] += sz[v];

            btree[nd].emplace_back(v);
            btree[v].emplace_back(nd);

            int cur = min(sz[v], N-sz[v]);
            if (cur >= gp[0].first && cur < msplit.second) {
                msplit = {v, cur};
            }
        }
    }
}

void dfsSZ (int nd, int par) {
    sz[nd] = 1;
    for (auto v : btree[nd]) {
        if (v != par) {
            dfsSZ(v, nd);
            sz[nd] += sz[v];
        }
    }
}

pii dfsCen (int nd, int par) {
    int mx = N - sz[nd];
    pii bst = {1, N};
    for (auto v : btree[nd]) {
        if (v != par) {
            pii res = dfsCen(v, nd);
            if (res.Y < bst.Y) {
                bst = res;
            }
            mx = max(mx, sz[v]);
        }
    }
    if (mx < bst.Y) {
        bst = {nd, mx};
    }
    return bst;
}

int centroid () {
    return dfsCen(0,-1).first;

}

vector<int> inv (const vector<int> &s) {
    memset(vis, 0, sizeof(vis));
    for (const auto v : s) {
        vis[v] = true;
    }
    vector<int> res;
    for (int i=0; i<N; i++) {
        if (!vis[i]) {
            res.emplace_back(i);
        }
    }
    return res;
}

bool inSet[MAXN];
bool vvs[MAXN];
void dfsN (int nd, int par, vector<int> &res, int &cnt, int g) {
    vvs[nd] = true;
    if (cnt < g) {
        cnt++;
        res.emplace_back(nd);
        for (auto v : edge[nd]) {
            if (!vvs[v] && inSet[v]) {
                dfsN(v, nd, res, cnt, g);
            }
        }
    }
}

vector<int> trim (const vector<int> &s, int g) {
    memset(inSet, 0, sizeof(inSet));
    for (auto v : s) {
        inSet[v] = true;
    }
    vector<int> ret;
    int cnt = 0;
    dfsN(s.front(), -1, ret, cnt, g);
    return ret;
}

struct Subtree {
    int sz;
    vector<int> element;

    Subtree () {
        sz = 0;
    }
};
vector<Subtree> child;

void dfsSub (int nd, int par, Subtree &cur) {
    cur.sz++;
    cur.element.eb(nd);
    for (auto v : btree[nd]) {
        if (par != v) {
            dfsSub(v, nd, cur);
        }
    }
}
int id[MAXN];

vector<int> sedg[MAXN];

int A;

bool vs[MAXN];
void dfsAns (int nd, vector<int> &res, int &wsum) {
    if (wsum >= A) {
        return;
    }
    vs[nd] = true;
    res.eb(nd);
    wsum += child[nd].sz;

    for (auto v : sedg[nd]) {
        if (!vs[v]) {
            dfsAns(v, res, wsum);
        }
    }
}


vector<int> find_split(int n, int a, int b, int c, vector<int> p, vector<int> q) {
    N = n;
	gp = {{a,1}, {b,2}, {c,3}};
	sort(gp.begin(), gp.end());
	A = gp[0].first;

    int m = p.size();
    for (int i=0; i<m; i++) {
        int u = p[i];
        int v = q[i];
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    span(0);
    int cen = centroid();
    debug(cen);

    int mx = 0;
    for (auto v : btree[cen]) {
        Subtree cur;
        dfsSub(v, cen, cur);
        for (auto el : cur.element) {
            id[el] = child.size();
        }

        debug(v, cur.element);
        if (cur.sz >= gp[0].first) {
            mx = child.size();
        }

        child.eb(cur);
    }

    vector<int> aset, bset;
    if (child[mx].sz >= gp[0].first) {
        aset = child[mx].element;
        bset = inv(aset);

        if (aset.size() > bset.size()) {
            swap(aset, bset);
        }
        assert(aset.size() >= gp[0].first);
        assert(bset.size() >= gp[1].first);
    } else {
        int cc = SZ(child);

        for (int i=0; i<m; i++) {
            int u = p[i];
            int v = q[i];
            if (u == cen || v == cen) {
                continue;
            }
            if (id[u] != id[v]) {
                sedg[id[u]].eb(id[v]);
                sedg[id[v]].eb(id[u]);
            }
        }

        bool fnd = false;
        for (int i=0; i<cc; i++) {
            if (!vs[i]) {
                vector<int> vec;
                int wsum = 0;
                dfsAns(i, vec, wsum);

                debug(vec, wsum);

                if (wsum >= gp[0].first) {
                    for (auto v : vec) {
                        for (auto nd : child[v].element) {
                            aset.eb(nd);
                        }
                    }
                    bset = inv(aset);
                    fnd = true;
                    break;
                }
            }
        }

        if (!fnd) {
            return vector<int>(n,0);
        }
    }

    if (aset.size() > bset.size()) {
        swap(aset, bset);
    }
    assert(aset.size() >= gp[0].first);
    assert(bset.size() >= gp[1].first);

    aset = trim(aset,gp[0].first);
    bset = trim(bset,gp[1].first);

//    assert(aset.size() == gp[0].first);
//    assert(bset.size() == gp[1].first);

    vector<int> ret(n, gp[2].second);
    for (auto v : aset) {
        ret[v] = gp[0].second;
    }
    for (auto v : bset) {
        ret[v] = gp[1].second;
    }

	return ret;
}
