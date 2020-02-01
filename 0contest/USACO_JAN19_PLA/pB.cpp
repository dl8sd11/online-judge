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

ll n,m;
vector<ll> edge[MAXN];
ll in[MAXN],out[MAXN];
ll w[MAXN];
vector<pii> query;


int anc[MAXLG][MAXN];
int dep[MAXN];

void dfs(int nd,int par){
  anc[0][nd] = par;
  dep[nd] = dep[par] + 1;
  for(int v:edge[nd]){
    if(v!=par) dfs(v,nd);
  }
}
void build_lca(){
  for(int i=1;i<MAXLG;i++){
    for(int j=1;j<=n;j++){
      anc[i][j] = anc[i-1][anc[i-1][j]];
    }
  }
}

int lca(int u,int v){
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

ll t[MAXN*4],t2[MAXN*4],N;
void build(){
  for(ll i=N-1;i>0;i--)t[i] = t[i<<1]+t[i<<1|1];
}
ll q(ll l,ll r){
  ll res = 0;
  for(l+=N,r+=N;l<r;l>>=1,r>>=1){
    if(l&1)res+=t[l++];
    if(r&1)res+=t[--r];
  }
  return res;
}

ll tot;
void DFS(ll nd,ll par) {
    in[nd] = tot++;
    t[in[nd]+N] = w[nd];
    for (auto v:edge[nd]) if (v != par) {
        DFS(v,nd);
    }
    out[nd] = tot++;
    t[out[nd]+N] = -w[nd];
}
/********** Good Luck :) **********/
int main()
{
    // IOS();
#ifndef tmd
    freopen("exercise.in","r",stdin);
    freopen ("exercise.out","w",stdout);
#endif
    cin >> n >> m;
    N = n*2;
    REP (i,n-1) {
        ll u,v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    REP (i,m-n+1) {
        ll u,v;
        cin >> u >> v;
        query.eb(u,v);
        w[u]++;
        w[v]++;
    }

    DFS(1,1);
    dfs(1,1);
    build_lca();
    build();

    pary(t+N,t+N*2);
    ll ans = 0;
    for (auto p:query) {
        ll ca = lca(p.X,p.Y);
        debug(p,ca);
        debug(in[ca],in[p.X]+1,in[p.Y]+1);
        ans += q(in[ca],in[p.X]+1) + q(in[ca],in[p.X]+1) + w[ca] - 2;
    }

    cout << ans / 2 << endl;
    return 0;
}
