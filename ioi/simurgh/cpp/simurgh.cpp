#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double, double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) static_cast<int>(i.size())
#define FOR(i, j, k, in) for (int i=j; i < (k) ; i+=in)
#define RFOR(i, j, k, in) for (int i=j; i >= (k) ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i, j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(), _a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
template<typename T, typename S>
istream &operator >> (istream &is, pair<T, S> &p) {
    return is >> p.X >> p.Y;
}
#ifdef tmd
#define TIME(i) Timer i(#i)
#define debug(...) do {\
    fprintf(stderr, "%s - %d (%s) = ", __PRETTY_FUNCTION__, __LINE__, #__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T> void _do(T &&_x) {cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x, S &&..._t) {cerr <<_x <<" ,"; _do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s, const pair<_a, _b> &_p) {return _s << "(" << _p.X << "," << _p.Y << ")";}
template<typename It> ostream& _OUTC(ostream &_s, It _ita, It _itb)
{
    _s << "{";
    for (It _it=_ita; _it != _itb; _it++) {
        _s <<(_it == _ita?"":",")<< *_it;
    }
    _s << "}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s, const vector<_a> &_c) {return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const array<_a,2> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const array<_a,3> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const array<_a,4> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const array<_a,5> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const set<_a> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const deque<_a> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s, const map<_a,_b> &_c) {return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
class Timer {
private:
    string scope_name;
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer (string name) : scope_name(name) {
        start_time = chrono::high_resolution_clock::now();
    }
    ~Timer () {
        auto stop_time = chrono::high_resolution_clock::now();
        auto length = chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
        double mlength = double(length) * 0.001;
        debug(scope_name, mlength);
    }
};
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif
#include "simurgh.h"

int n, dfs_time;
vector<vector<pii> > edge;
vector<int> fat, fid, dfn;
vector<pii> low, G;

vector<int> tree;
vector<int> gold;
void dfs (int nd, int par) {
    dfn[nd] = dfs_time++;
    low[nd] = {dfn[nd], -1};
    for (auto &[u,id] : edge[nd]) {
        if (u == par) continue;
        if (dfn[u] == -1) { // tree
            fat[u] = nd;
            fid[u] = id;
            dfs(u, nd);
            low[nd] = min(low[nd], low[u]);
            tree.eb(id);
        } else if (dfn[u] < dfn[nd]) {
            low[nd] = min(low[nd], pii(dfn[u], id));
        }
    }
    if (low[nd].X == dfn[nd] && par != -1) {
        gold[fid[nd]] = 1;
        debug(fid[nd]);
    }
}

struct Djs {
    vector<int> djs;
    Djs(int N) : djs(N) {
        iota(ALL(djs), 0);
    }
    int fnd (int x) {
        return x == djs[x] ? x : djs[x] = fnd(djs[x]);
    }
    bool mrg (int x, int y) {
        x = fnd(x), y = fnd(y);
        if (x == y) return false;
        djs[fnd(x)] = fnd(y);
        return true;
    }
};

void build_cycle (vector<int> cycle) {
    vector<int> res;
    debug(cycle);
    for (int i=0; i<SZ(cycle); i++) {
        Djs djs(n);
        vector<int> qry;
        for (int j=0; j<SZ(cycle); j++) {
            if (i != j) {
                qry.eb(cycle[j]);
                assert(djs.mrg(G[cycle[j]].X, G[cycle[j]].Y));
            }
        }
        for (int id : tree) {
            if (djs.mrg(G[id].X, G[id].Y)) {
                qry.eb(id);
            }
        }
        res.eb(count_common_roads(qry));
    }

    debug(res);
    int mn = *max_element(ALL(res));
    for (int i=0; i<SZ(cycle); i++) {
        gold[cycle[i]] = (res[i] == mn) ? -1 : 1;
    }
}

void build_alt (vector<int> cycle, int known, int want) {

    vector<int> res;
    debug(cycle, known, want);
    for (int i : {known, want}) {
        Djs djs(n);
        vector<int> qry;
        for (int j=0; j<SZ(cycle); j++) {
            if (i != cycle[j]) {
                qry.eb(cycle[j]);
                assert(djs.mrg(G[cycle[j]].X, G[cycle[j]].Y));
            }
        }
        for (int id : tree) {
            if (djs.mrg(G[id].X, G[id].Y)) {
                qry.eb(id);
            }
        }
        res.eb(count_common_roads(qry));
    }

    gold[want] = gold[known] * ((res[0] == res[1]) ? 1 : -1);
}

void check (int id) {
    if (gold[id]) return;
    int be = low[G[id].Y].Y;
    int nd = G[be].Y;
    vector<int> cycle = {be};

    int known = -1;
    while (nd != G[be].X) {
        if (gold[fid[nd]]) known = fid[nd];
        cycle.eb(fid[nd]);
        nd = fat[nd];
    }
    
    if (known == -1) build_cycle(cycle);
    else build_alt(cycle, known, id);
}

void bin_gold (int nd) {
    int cnt = 0;

    vector<int> E;
    for (auto &[_,id]: edge[nd]) {
        if (gold[id] == 0) E.eb(id);
    }

    int lst = 0;
    while (cnt < SZ(E)) {
        int L = lst, R = SZ(E) + 1;
        while (L < R - 1) {
            int M = (L + R) >> 1;
            vector<int> qry;
            Djs djs(n);
            for (int i=0; i<M; i++) {
                qry.eb(E[i]);
                assert(djs.mrg(G[E[i]].X, G[E[i]].Y)); 
            }
            int tree_gold = 0;
            for (int id : tree) {
                if (djs.mrg(G[id].X, G[id].Y)) {
                    tree_gold += gold[id] == 1;
                    qry.eb(id);
                }
            }

            int sum = count_common_roads(qry) - tree_gold;
            if (sum > cnt) R = M;
            else L = M;
        }
        debug(nd, cnt, R);
        if (R == SZ(E) + 1) break;
        else gold[E[R-1]] = 1;
        cnt++;
        lst = R;
    }
    for (int id : E) {
        if (gold[id] == 0) gold[id] = -1;
    }
}

std::vector<int> find_roads(int N, std::vector<int> u, std::vector<int> v) {
    n = N;
    dfs_time = 0;
    edge.resize(n);
    fat.resize(n);
    fid.resize(n);
    low.resize(n);
    dfn.resize(n, -1);
    gold.resize(SZ(u));
    for (int i=0; i<SZ(u); i++) {
        edge[u[i]].eb(v[i], i);
        edge[v[i]].eb(u[i], i);
        G.eb(v[i], u[i]);
    }
    debug(N, G);
    dfs(0, -1);
    for (int id=0; id<SZ(G); id++) {
        if (dfn[G[id].X] > dfn[G[id].Y]) {
            swap(G[id].X, G[id].Y);
        }
    }

    for (int id : tree) {
        check(id);
        debug(id, gold[id]);
    }

    for (int i=0; i<n; i++) {
        bin_gold(i);
    }
    debug(gold);

    vector<int> ans;
    for (int i=0; i<SZ(G); i++) {
        if (gold[i] == 1) ans.eb(i);
    }
    assert(ans.size() == n-1);
    return ans;

}
