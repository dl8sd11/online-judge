#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) ll(i.size())
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
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
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

template<class T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template<class T> using MaxHeap = priority_queue<T>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

const ll MOD=1000000007;
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAXN=2e5+5;
const ll MAXLG=__lg(MAXN)+2;


/* Disjoint Set */
ll djs[MAXN],sz[MAXN];
void init() {
    REP (i,MAXN) {
        djs[i] = i;
        sz[i] = 1;
    }
}

ll fnd(ll x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

void uni(ll x,ll y) {
    if (sz[x=fnd(x)] > sz[y=fnd(y)]) {
        swap(x,y);
    }
    djs[x] = y;
    sz[y] += sz[x];
}
/* End Disjoint Set */
ll n,m;
struct E {
    bool is_tree;
    ll u,v,w;
};
vector<E> edge;
vector<pii> g[MAXN];

ll anc[MAXLG][MAXN],mx[MAXLG][MAXN],dep[MAXN];

void dfs(ll nd,ll par) {
    anc[0][nd] = par;
    dep[nd] = dep[par] + 1;
    for (auto v:g[nd]) if (v.X != par) {
        mx[0][v.X] = v.Y;
        dfs(v.X,nd);
    }
}

void build_lca() {
    REP1 (i,MAXLG-1) {
        REP1 (j,n) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
            mx[i][j] = max(mx[i-1][j],mx[i-1][anc[i-1][j]]);
        }
    }
}

ll query(ll u,ll v) {
    ll ret = 0;

    if (dep[u] < dep[v]) {
        swap(u,v);
    }
    for (ll i=MAXLG-1;i>=0;i--) {
        if (dep[anc[i][u]] >= dep[v]) {
            ret = max(ret,mx[i][u]);
            u = anc[i][u];
        }
    }

    if (u == v) {
        return ret;
    }

    for (ll i=MAXLG-1;i>=0;i--) {
        if (anc[i][u] != anc[i][v]) {
            ret = max(ret,mx[i][u]);
            ret = max(ret,mx[i][v]);
            u = anc[i][u];
            v = anc[i][v];
        }
    }

    return max(ret,max(mx[0][u],mx[0][v]));
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP (i,m) {
        ll u,v,w;
        cin >> u >> v >> w;
        edge.push_back({0,u,v,w});
    }

    sort(ALL(edge),[&](const E &e1,const E &e2){return e1.w < e2.w;});

    init();
    REP (i,m) {
        if (fnd(edge[i].u) != fnd(edge[i].v)) {
            uni(edge[i].u,edge[i].v);
            edge[i].is_tree = true;
            g[edge[i].u].eb(edge[i].v,edge[i].w);
            g[edge[i].v].eb(edge[i].u,edge[i].w);
        }
    }

    dfs(1,1);
    build_lca();

    ll ans = 0;
    REP (i,m) {
        if (!edge[i].is_tree) {
            if (query(edge[i].u,edge[i].v) == edge[i].w) {
                ans++;
            }
        }
    }
    
    cout << ans << endl;
    return 0;
}
