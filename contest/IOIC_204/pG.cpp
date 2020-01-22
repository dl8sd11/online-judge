#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<(k) ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=(k) ; i-=in)
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

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const int MAXN = 500005;
const int MAXLG = __lg(MAXN) + 3;

ll n, q;
vector<ll> edge[MAXN];
pair<ll,ll> dia;
ll len;

int anc[MAXLG][MAXN];
int dep[MAXN];
void dfs (ll nd, ll par) {
    anc[0][nd] = par;
    dep[nd] = dep[par] + 1;

    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v, nd);
        }
    }
}

void build_lca_nd (ll nd) {
    REP1 (i, MAXLG-1) {
        anc[i][nd] = anc[i-1][anc[i-1][nd]];
    }
}

void build_lca () {
    REP1 (i, MAXLG-1) {
        REP1 (j, n) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }
}

ll dist (ll u, ll v) {
    ll ou = u, ov = v;
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    for (ll i=MAXLG-1;i>=0;i--) {
        if (dep[anc[i][u]] >= dep[v]) {
            u = anc[i][u];
        }
    }
    if (u == v) {
        return dep[ou] - dep[u] + dep[ov] - dep[u];
    }

    for (ll i=MAXLG-1;i>=0;i--) {
        if (anc[i][u] != anc[i][v]) {
            u = anc[i][u];
            v = anc[i][v];
        }
    }

    return dep[ou] + dep[ov] - 2 * dep[anc[0][u]];
}

pair<ll,ll> fpt (ll nd, ll par) { // nd, dist
    pii ret = {nd, 0};
    for (auto v : edge[nd]) {
        if (v != par) {
            pii cur = fpt(v, nd);
            if (cur.Y + 1 > ret.Y) {
                ret = cur;
                ret.Y++;
            }
        }
    }
    return ret;
}

void build_dia () {
    dia.X = fpt(1, -1).X;
    pii ret = fpt(dia.X, -1);
    dia.Y = ret.X;
    len = ret.Y;
}

void check_dia (ll u, ll v) {
    ll dis = dist(u, v);
    if (dis > len) {
        len = dis;
        dia = {u, v};
    }
}

void add_edge (ll u, ll lf) {
    #ifdef tmd
    edge[u].emplace_back(lf);
    edge[lf].emplace_back(u);
    #endif
    anc[0][lf] = u;
    build_lca_nd(lf);
    dep[lf] = dep[u] + 1;

    pii cd = dia;
    check_dia(cd.X, lf);
    check_dia(cd.Y, lf);
}

void bf_check() {
    int tmp = len;
    build_dia();
    assert(tmp == len);
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n >> q;

    REP (i, n-1) {
        ll u, v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    dfs(1, 1);
    build_dia();
    build_lca();
    debug(len, dia);

    ll L = 0;

    int cn = n;
    REP1 (_u, q) {
        ll x, y;

        #ifdef tmdd
        x = cn;
        y = ++cn;
        #else
        cin >> x >> y;
        x ^= L;
        y ^= L;
        #endif
        // debug(x,y);

        add_edge(x, y);
        // assert(y == _u + n);
        #ifdef tmdd
        bf_check();
        #endif


        L = len;
        cout << L << endl;
    }

    return 0;
}
