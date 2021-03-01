#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
typedef pair<int, int> pii;
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
#define f first
#define s second
#define MX(a,b) a=max(a,b)
#define MN(a,b) a=min(a,b)
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
const int MAXLG = 21;
const int MAXN = 3e5+5;
const int maxn = MAXN;

int anc[MAXLG][MAXN];
int dep[MAXN];
vector<int> edge[MAXN];
void dfs(int nd,int par){
  anc[0][nd] = par;
  dep[nd] = dep[par] + 1;
  for(int v:edge[nd]){
    if(v!=par) dfs(v,nd);
  }
}
void build_lca(){
  for(int i=1;i<MAXLG;i++){
    for(int j=0;j<maxn;j++){
      anc[i][j] = anc[i-1][anc[i-1][j]];
    }
  }
}

int query(int u,int v){
  if(dep[u] < dep[v])swap(u,v);
  for(int i=MAXLG-1;i>=0;i--){
    if(dep[anc[i][u]] >= dep[v]) u = anc[i][u];
  }
  if(u==v)return u;

  for(int i=MAXLG-1;i>=0;i--){
    if(anc[i][u] != anc[i][v]) {
      u = anc[i][u];
      v = anc[i][v];
    }
  }

  return anc[0][u];
}

int v[maxn];
vector<pii> g[maxn];

int qme[maxn]; // size of 2
int qbest[maxn];
int qlca[maxn];

vector<int> totop[maxn];

int s[maxn*4], sum[maxn*4], ls[maxn*4], rs[maxn*4];

void MO(int p, int v, int o = 1, int l = 0, int r = maxn-1){
    if (l > p || r < p) {
        return;
    }
    if (l == r) {
        s[o] = ls[o] = rs[o] = max(0ll,v);
        sum[o] = v;
        return;
    }
    int mid = (l+r)/2;
    MO(p,v,o*2,l,mid);
    MO(p,v,o*2+1,mid+1,r);
    s[o] = max({s[o*2], s[o*2+1], rs[o*2] + ls[o*2+1]});
    sum[o] = sum[o*2] + sum[o*2+1];
    ls[o] = max(ls[o*2], sum[o*2] + ls[o*2+1]);
    rs[o] = max(rs[o*2+1], sum[o*2+1] + rs[o*2]);
}

struct Info{
    int s,ls,rs,sum;
};

Info QU(int L, int R, int o = 1, int l = 0, int r = maxn-1) {
    if (l > R || r < L || L > R) {
        return {0,0,0,0};
    }
    if (l >= L && r <= R) {
        return {s[o], ls[o], rs[o], sum[o]};
    }
    int mid = (l+r)/2;
    Info a = QU(L,R,o*2,l,mid), b = QU(L,R,o*2+1,mid+1,r);
    return {
        max({a.s, b.s, a.rs + b.ls}),
        max(a.ls, a.sum + b.ls), 
        max(b.rs, b.sum + a.rs),
        a.sum + b.sum
    };
}

void DFS(int v, int p) {
    for (int qn : totop[v]) {
        int L = dep[qlca[qn]];
        Info gt = QU(L,maxn-1);
        qbest[qn] = max(qbest[qn], gt.s);
        qme[qn] += gt.ls;
    }
    for (pii ed : g[v]) {
        int u = ed.f;
        if (u == p) continue;
        MO(dep[v], ed.s);
        DFS(u,v);
        MO(dep[v], -0x3f3f3f3f);
    }
    
}

signed main () {
    TIME(main);
    IOS();
    int n,q; cin>>n>>q;
    for (int i = 0; i<n-1; ++i) {
        int a,b,c; cin>>a>>b>>c;
        --a; --b;
        edge[a].pb(b);
        edge[b].pb(a);
        g[a].pb({b,c});
        g[b].pb({a,c});
    }
    dfs(0,0);
    build_lca();
    vector<vector<pii > > qat (n);
    for (int i = 0; i<q; ++i) {
        int a,b; cin>>a>>b; --a; --b;
        int L = query(a,b);
        qlca[i] = L;
        totop[a].pb(i);
        totop[b].pb(i);
    }
    DFS(0,-1);
    for (int i = 0; i<q; ++i) {
        debug(qme[i], qbest[i]);
        cout<<max(qme[i], qbest[i])<<endl;
    }
    return 0;
}
