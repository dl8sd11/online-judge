#include "werewolf.h"
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
    return os << "{" << v.X << "," <<v.Y << "}";
}
template<typename T> ostream &operator << (ostream &os, const vector<T> &v) {
    return __printRng(os, ALL(v));
}
template<typename T> ostream &operator << (ostream &os, const set<T> &v) {
    return __printRng(os, ALL(v));
}
#define IOS()
#else
#define debug(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#endif

struct Djsrng {
    vector<int> djs, sz, l, r, vis;
    int N;
    Djsrng (int n, vector<int> id) : djs(n), sz(n,1), l(n), r(n), vis(n, 0) {
        N = n;
        iota(ALL(djs), 0);
        for (int i=0; i<n; i++) {
            l[i] = r[i] = id[i];
        }
    }

    int fnd (int x) {
        return x == djs[x] ? x : djs[x] = fnd(djs[x]);
    }

    void mrg (int x, int y) {
        x = fnd(x), y = fnd(y);
        if (x == y) return;
        if (sz[x] > sz[y]) swap(x, y);
        djs[x] = y;
        sz[y] += sz[x];
        l[y] = min(l[y], l[x]);
        r[y] = max(r[x], r[y]);
    }
};

struct Djsid {
    vector<vector<int> > tree;
    vector<int> djs, sz, id, vis;
    int ncnt, N;
    Djsid (int n) : tree(n*2), djs(n), sz(n,1), id(n), vis(n, 0) {
        N = n;
        iota(ALL(djs), 0);
        iota(ALL(id), 0);
        ncnt = n;
    }

    int fnd (int x) {
        return x == djs[x] ? x : djs[x] = fnd(djs[x]);
    }

    void mrg (int x, int y) {
        x = fnd(x), y = fnd(y);
        if (x == y) return;
        if (sz[x] > sz[y]) swap(x, y);
        djs[x] = y;
        sz[y] += sz[x];
        tree[ncnt].eb(id[x]);
        tree[ncnt].eb(id[y]);
        id[y] = ncnt++;
    }

    void dfs (int nd, vector<int> &res, int &id) {
        if (tree[nd].empty()) res[nd] = id++;
        for (int v : tree[nd]) {
            dfs(v, res, id);
        }
    }

    vector<int> build () {
        vector<int> res(N);
        int id=0;
        dfs(ncnt-1, res, id);
        assert(ncnt == N*2-1);
        return res;
    }
};

vector<int> genId (int n, const vector<vector<int> > &edge, bool rev) {
    vector<int> ord(n);
    iota(ALL(ord), 0);
    if (rev) reverse(ALL(ord));

    Djsid djs(n);
    for (int u : ord) {
        djs.vis[u] = true;
        for (int v : edge[u]) {
            if (djs.vis[v]) {
                djs.mrg(u, v);
            }
        }
    }
    return djs.build();
}

vector<pii> genRng (int n, const vector<vector<int> > &edge, const vector<int> &id, int rev, vector<int> x, vector<int> lim) {
    int q = SZ(x);
    vector<pii> res(q);
    vector<int> ord(n);
    iota(ALL(ord), 0);
    if (rev) reverse(ALL(ord));

    vector<vector<int> > qry(n);
    for (int i=0; i<q; i++) {
        qry[lim[i]].eb(i);
    }
    Djsrng djs(n, id);
    for (int u : ord) {
        djs.vis[u] = true;
        for (int v : edge[u]) {
            if (djs.vis[v]) {
                djs.mrg(u, v);
            }
        }
        for (int qid : qry[u]) {
            res[qid] = {djs.l[djs.fnd(x[qid])],
                        djs.r[djs.fnd(x[qid])]};
        }
    }
    return res;
}

struct bit_2d {
    vector<vector<int> > bit;
    int N;

    bit_2d (int n): bit(n+3) {
        N = n + 3;
    }

    void add (int x, int y) {
        for (x++; x<N; x+=-x&x) {
            bit[x].eb(y);
        }
    }

    void build () {
        for (auto &v : bit) {
            sort(ALL(v));
        }
    }

    int qry (int x, int yl, int yr) {
        int res = 0;
        for (x++; x; x-=-x&x) {
            res += upper_bound(ALL(bit[x]), yr) - 
                   lower_bound(ALL(bit[x]), yl);
        }
        return res;
    }

    int qry (int xl, int xr, int yl, int yr) {
        return qry(xr, yl, yr) - qry(xl-1, yl, yr);
    }
};

vector<int> check_validity(int n, vector<int> x, vector<int> y,
                                vector<int> s, vector<int> e,
                                vector<int> l, vector<int> r) {
    vector<vector<int> > edge(n, vector<int>());
    for (int i=0; i<SZ(x); i++) {
        edge[x[i]].eb(y[i]);
        edge[y[i]].eb(x[i]);
    }
    vector<int> fid = genId(n, edge, 0);
    vector<int> sid = genId(n, edge, 1);
    debug(fid, sid);

    vector<pii> frng = genRng(n, edge, fid, 0, e, r);
    vector<pii> srng = genRng(n, edge, sid, 1, s, l);
    debug(frng, srng);

    bit_2d dt(n);
    for (int i=0; i<n; i++) {
        dt.add(fid[i], sid[i]);
    }
    dt.build();

    vector<int> ans;
    for (int i=0; i<SZ(frng); i++) {
        int res = dt.qry(frng[i].X, frng[i].Y, srng[i].X, srng[i].Y);
        debug(res);
        ans.eb(res > 0);
    }

    return ans;
}
