#include "simurgh.h"
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define SZ(i) int(i.size())
#define ALL(i) i.begin(), i.end()
#define MEM(i,a) memset(i, (a), sizeof(i))
#define X first
#define Y second
#define eb emplace_back
#define pb push_back
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d-(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do (T &&x) {cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y) {cerr<<x<<", ";_do(y...);}
template<typename IT> ostream& __printRng (ostream &os, IT bg, IT ed) {
    for (IT it=bg; it!=ed; it++) {
        if (it!=bg) os << "," << *it;
        else os << "{" << *it;
    }
    return os << "}";
}
template<typename T> ostream &operator << (ostream &os, const pair<T,T> &v) {
    return os << "{" << v.X <<","<<v.Y<<"}";

}
template<typename T> ostream &operator << (ostream &os, const vector<T> &v) {
    return __printRng(os, ALL(v));
}
template<typename T> ostream &operator << (ostream &os, const set<T> &v) {
    return __printRng(os, ALL(v));
}
#else
#define debug(...)
#endif

const int MAXN = 502;
vector<pii> edge[MAXN];
vector<pii> euv;

int m, n;
set<int> rem, good;
bool is_good[MAXN*MAXN];
bool is_rem[MAXN*MAXN];

int pid[MAXN], fat[MAXN], dep[MAXN];
void dfs_c (int nd, int par, vector<int> &cid) {
    fat[nd] = par;
    dep[nd] = dep[par] + 1;
    for (auto p : edge[nd]) {
        if (cid.size()) return;
        int u, id;
        tie(u, id) = p;
        if (is_rem[id] == 0) continue;
        if (u != par) {
            if (dep[u] != 0) {
                if (dep[u] > dep[nd]) continue;
                vector<int> nw;
                nw.eb(id);
                int cur = nd;
                while (cur != u) {
                    nw.eb(pid[cur]);
                    cur = fat[cur];
                }
                cid = nw;
                if (nw.size() > cid.size()) cid = nw;
                return;
            } else {
                pid[u] = id;
                dfs_c(u, nd, cid);
            }
        }
    }
}

vector<int> rem_cycle () {
    MEM(pid, -1);
    MEM(dep, 0);
    for (int i=0; i<n; i++) {
        if (pid[i] == -1) {
            vector<int> cur;
            dfs_c(i, i, cur);
            if (cur.size()) return cur;
        }
    }
    return vector<int>();
}

int djs[MAXN], sz[MAXN];

void init () {
    for (int i=0; i<n; i++) {
        djs[i] = i;
        sz[i] = 1;
    }
}

int fnd (int x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

bool mrg (int x, int y) {
    x = fnd(x), y = fnd(y);
    if (x == y) return false;
    if (sz[x] > sz[y]) swap(x, y);
    djs[x] = y;
    return true;
}

vector<int> span (vector<int> cyc) {
    init();
    for (int v : cyc) {
        mrg(euv[v].X, euv[v].Y);
    }
    vector<int> res;
    for (int i=0; i<m; i++) {
        if (mrg(euv[i].X, euv[i].Y)) {
            res.eb(i);
        }
    }
    return res;
}

set<int> trees;
void dfs_t (int nd, int par) {
    dep[nd] = dep[par] + 1;
    fat[nd] = par;
    for (auto p : edge[nd]) {
        int u, id;
        tie(u, id) = p;
        if (trees.count(id) == 0) continue;
        if (u == par) continue;
        pid[u] = id;
        dfs_t(u, nd);
    }

}

int count_common_roads(const std::set<int> &r) {
    vector<int> v;
    for (auto e : r) v.eb(e);
    return count_common_roads(v);
}

void srem () {
    init();
    debug(good.size(), rem.size());
    trees.clear();
    if (good.size() + rem.size() == n-1) {
        for (int v : rem) {
            good.insert(v);
        }
        rem.clear();
        return;
    }
    for (int g : good) {
        trees.insert(g);
        mrg(euv[g].X, euv[g].Y);
    }
    int fail = -1;
    for (int g : rem) {
        if (mrg(euv[g].X, euv[g].Y)) {
            trees.insert(g);
        } else {
            fail = g;
        }
    }
    debug(trees);
    assert(fail != -1);
    dfs_t(0, 0);
    int swp = -1;
    int u, v;
    tie(u, v) = euv[fail];

    while (u != v) {
        if (dep[u] > dep[v]) swap(u, v);
        if (good.count(pid[v])) swp = pid[v];
        v = fat[v];
    }
    assert(swp != -1);

    int org = count_common_roads(trees);
    trees.erase(swp);
    trees.insert(fail);
    int nw = count_common_roads(trees);
    if (nw == org) {
        good.insert(fail);
    }
    rem.erase(fail);
    is_rem[fail] = false;
}

std::vector<int> find_roads(int _n, std::vector<int> u, std::vector<int> v) {
    n = _n;
    m = SZ(u);

    for (int i=0; i<m; i++) {
        rem.insert(i);
        is_rem[i] = true;
        euv.eb(u[i], v[i]);
        edge[u[i]].eb(v[i], i);
        edge[v[i]].eb(u[i], i);
    }


    debug(euv);
    while (true) {
        vector<int> cyc = rem_cycle();
        if (cyc.empty()) break;
        debug(cyc);
        assert(cyc.size() > 2);

        vector<int> sp = span(cyc);
        vector<pii> res;
        int csz = SZ(cyc);
        for (int i=0; i<csz; i++) {
            for (int j=0; j<csz; j++) {
                if (i != j) sp.eb(cyc[j]);
            }
            res.eb(count_common_roads(sp), cyc[i]);
            for (int j=0; j<csz-1; j++) sp.pop_back();
        }
        sort(ALL(res));
        for (auto p : res) {
            if (p.X != res.back().X) {
                good.insert(p.Y);
            }
            rem.erase(p.Y);
            is_rem[p.Y] = false;
        }
        debug(res);
    }
    debug(good);
    debug(rem);

    while (good.size() < n - 1) {
        srem();
    }

    vector<int> ans;
    for (int x : good) ans.eb(x);
    return ans;
}

