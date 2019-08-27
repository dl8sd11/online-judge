#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#ifdef tmdd
#define TIME(i) Timer i(#i)
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<" ,";_do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s,const pair<_a,_b> &_p){return _s<<"("<<_p.X<<","<<_p.Y<<")";}
template<typename It> ostream& _OUTC(ostream &_s,It _ita,It _itb)
{
    _s<<"{";
    for(It _it=_ita;_it!=_itb;_it++)
    {
        _s<<(_it==_ita?"":",")<<*_it;
    }
    _s<<"}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s,vector<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,set<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif
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

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 1000000000;
const ll MAXN = 100005;
const ll MAXLG = __lg(MAXN) + 3;

int djs[MAXN], n, m, anc[MAXLG][MAXN], mx[MAXLG][MAXN], dep[MAXN], tp[MAXN], sz[MAXN], fat[MAXN], in[MAXN], out[MAXN];
int fnd (int x) {
    return djs[x] == x ? x : djs[x] = fnd(djs[x]);
}

bool mrg (int x, int y) {
    x = fnd(x), y = fnd(y);
    if (x == y) {
        return false;
    }
    djs[x] = y;
    return true;
}

struct Edge {
    int a, b, w, id;
    bool is_tree;
} edge[MAXN * 10];

ostream& operator << (ostream &_s,const Edge &_p){
    return _s<<"("<<_p.a<<","<<_p.b<<","<<_p.w<<","<<_p.id<<","<<_p.is_tree<<")";
}
vector<pair<int,int> > g[MAXN];

void dfs (int nd, int par) {
    anc[0][nd] = par;
    sz[nd] = 1;
    dep[nd] = dep[par] + 1;
    for (auto p : g[nd]) {
        if (p.X != par) {
            mx[0][p.X] = p.Y;
            dfs(p.X, nd);
            sz[nd] += sz[p.X];
            if (sz[p.X] > sz[fat[nd]]) {
                fat[nd] = p.X;
            }
        }
    }
}

int ts;
void build_hld (int nd, int par, int t) {
    tp[nd] = t;
    in[nd] = ts++;
    if (fat[nd]) {
        build_hld(fat[nd], nd, t);
    }
    for (auto v : g[nd]) {
        if (v.X != par && v.X != fat[nd]) {
            build_hld(v.X, nd, v.X);
        }
    }
    out[nd] = ts;
}

void build_lca () {
    REP1 (i, MAXLG - 1) {
        REP1 (j, n) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
            mx[i][j] = max(mx[i-1][j], mx[i-1][anc[i-1][j]]);
        }
    }
}

int max_edge (int u, int v) {
    int ret = -iNF;
    if (dep[u] > dep[v]) {
        swap(u, v);
    }
    RREP (i, MAXLG - 1) {
        if (dep[anc[i][v]] >= dep[u]) {
            ret = max(ret, mx[i][v]);
            v = anc[i][v];
        }
    }

    if (u == v) {
        return ret;
    }

    RREP (i, MAXLG - 1) {
        if (anc[i][v] != anc[i][u]) {
            ret = max(ret, mx[i][v]);
            ret = max(ret, mx[i][u]);
            v = anc[i][v];
            u = anc[i][u];
        }
    }
    
    return max({ret, mx[0][u], mx[0][v]});
}

int seg[MAXN * 2];
void add (int l, int r, int v) {
    for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
        if (l&1) {
            seg[l] = min(seg[l], v);
            l++;
        }
        if (r&1) {
            r--;
            seg[r] = min(seg[r], v);
        }
    }
}

int qry (int x) {
    int ret = iNF;
    for (x+=n; x>=1; x>>=1) {
        ret = min(ret, seg[x]);
    }
    return ret;
}

void chg (int u, int v, int w) {
    while (tp[u] != tp[v]) {
        debug(u, v, w);
        if (dep[tp[u]] > dep[tp[v]]) {
            swap(u, v);
        }
        add(in[tp[v]], in[v]+1, w);
        v = anc[0][tp[v]];
    }
    if (dep[u] > dep[v]) {
        add(in[v]+1, in[u]+1, w);
        debug(in[v]+1, in[u]+1, w);
    } else {
        add(in[u]+1, in[v]+1, w);
        debug(in[u]+1, in[v]+1, w);
    } 
} 

int ans[MAXN*10];
/********** Good Luck :) **********/
int main()
{
    TIME(main);
    IOS();

    cin >> n >> m;
    REP (i, m) {
        cin >> edge[i].a >> edge[i].b >> edge[i].w;
        edge[i].id = i;
    }

    sort(edge, edge+m, [&](Edge e1, Edge e2) {
        return e1.w < e2.w;
    });

    REP1 (i, n) {
        djs[i] = i;
    }
    REP (i, m) {
        edge[i].is_tree = mrg(edge[i].a, edge[i].b);
        if (edge[i].is_tree) {
            g[edge[i].a].eb(edge[i].b, edge[i].w);
            g[edge[i].b].eb(edge[i].a, edge[i].w);
        }
    }

    mx[0][1] = -iNF;
    dfs(1, 1);
    build_lca();
    build_hld(1, 1, 1);
    pary(tp+1, tp+n+1);
    pary(in+1, in+n+1);

    sort(edge, edge+m, [&](Edge e1, Edge e2) {
        return e1.id < e2.id;
    });

    REP (i, n*2) {
        seg[i] = iNF;
    }
    REP (i, m) {
        if (!edge[i].is_tree) {
            ans[i] = max_edge(edge[i].a, edge[i].b);
            chg(edge[i].a, edge[i].b, edge[i].w);
        }
    }

    REP (i, m) {
        if (edge[i].is_tree) {
            if (dep[edge[i].a] > dep[edge[i].b]) {
                ans[i] = qry(in[edge[i].a]);
                debug(edge[i].a);
            } else {
                debug(edge[i].b);
                ans[i] = qry(in[edge[i].b]);
            }
        }
    }
    pary(seg,seg+2*n);

    REP (i, m) {
        cout << ans[i] << " \n"[i==m-1];
    }
    return 0;
}
/*
11 11
1 2 2 
3 1 3
4 2 4
5 3 5 
6 3 6
7 4 7
8 7 8
9 4 9
10 4 10
11 10 11
10 5 20

*/
