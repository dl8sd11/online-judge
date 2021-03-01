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
#ifdef tmd
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
const int iNF = 0x3f3f3f3f;
const ll MAXN = 100005;
const ll MAXLG = __lg(MAXN) + 3;

int djs[MAXN], n, m, anc[MAXLG][MAXN], mx[MAXLG][MAXN], dep[MAXN];
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
    dep[nd] = dep[par] + 1;
    for (auto p : g[nd]) {
        if (p.X != par) {
            mx[0][p.X] = p.Y;
            dfs(p.X, nd);
        }
    }
}

void build_lca () {
    REP1 (i, MAXLG - 1) {
        REP1 (j, n) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
            mx[i][j] = max(mx[i-1][j], mx[i-1][anc[i-1][j]]);
        }
    }
    REP (i, 3) {
        pary(anc[i]+1, anc[i]+n+1);
        pary(mx[i]+1, mx[i]+n+1);
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
    debug(u, v, ret);

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
        debug(edge[i]);
    }

    mx[0][1] = -iNF;
    dfs(1, 1);
    build_lca();

    sort(edge, edge+m, [&](Edge e1, Edge e2) {
        return e1.id < e2.id;
    });

    REP (i, m) {
        if (!edge[i].is_tree) {
            cout << max_edge(edge[i].a, edge[i].b) << endl;
        }
    }

    return 0;
}
