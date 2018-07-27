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
const ll MAXN=1e3+5;
const ll MAXLG=__lg(MAXN)+2;
ll n,m,cx,cy,cw,ans1,ans2;
vector<pii> edge;
vector<pii> edgeW;
vector<pii> not_tree_edge;
vector<pii> tedge[MAXN];
ll dep[MAXN],fat[MAXLG][MAXN],mx[MAXLG][MAXN];
ll djs[MAXN],sz[MAXN];
void init(){
  REP(i,MAXN) djs[i]=i,sz[i]=1;
}
ll Find(ll x){
  return (djs[x]==x?x:djs[x]=Find(djs[x]));
}
void Union(ll x,ll y){
  if(sz[x=Find(x)]>sz[y=Find(y)])swap(x,y);
  djs[x]=y;
  sz[y]+=sz[x];
}
void dfs(ll nd,ll par){
  for(auto v:tedge[nd]){
    if(v.X==par)continue;
    dep[v.X] = dep[nd] + 1;
    fat[0][v.X] = nd;
    mx[0][v.X] = v.Y;
    dfs(v.X,nd);
  }
}
void build(){
  REP1(i,MAXLG-1){
    REP(j,MAXN){
      fat[i][j] = fat[i-1][fat[i-1][j]];
      mx[i][j] = max(mx[i-1][j],mx[i-1][fat[i-1][j]]);
    }
  }
}
ll lca(ll u,ll v){
  ll tu = u,tv = v;
  ll ret = 0;
  if(dep[u]>dep[v])swap(u,v);
  RREP(i,MAXLG-1){
    if(dep[fat[i][v]] >= dep[u]) cmax(ret,mx[i][v]),v = fat[i][v];
  }
  debug(u,v);
  if(u==v){
    debug(tu,tv,v);
    return ret;
  }
  RREP(i,MAXLG-1){
    if(fat[i][u] != fat[i][v]) {
      cmax(ret,max(mx[i][v],mx[i][u]));
      u = v = fat[i][u];
    }
  }
  debug(tu,tv,fat[0][u]);
  return max(ret,max(mx[0][u],mx[0][v]));
}
/********** Main()  function **********/
int main()
{
  IOS();
  cin>>n>>m;
  REP(i,m){
    cin>>cx>>cy>>cw;
    edge.pb({cx,cy});
    edgeW.pb({cw,i});
  }
  sort(ALL(edgeW));

  ans1 = 0;
  init();
  for(auto id:edgeW){
    ll x = edge[id.Y].X,y = edge[id.Y].Y;
    if(Find(x)!=Find(y)){
      Union(x,y);
      ans1+=id.X;
      tedge[x].pb({y,id.X});
      tedge[y].pb({x,id.X});
    } else {
      not_tree_edge.pb(id);
    }
  }
  REP1(i,n-1)if(Find(i)!=Find(i+1)){
    cout<<"-1 -1"<<endl;
    return 0;
  }
  if(not_tree_edge.empty()){
    cout<<ans1<<" -1"<<endl;
    return 0;
  }
  dep[1] = 0;
  fat[0][1] = 1;
  dfs(1,1);
  build();

  ans2 = INF;
  for(auto ed:not_tree_edge){
    cmin(ans2,ans1-lca(edge[ed.Y].X,edge[ed.Y].Y)+ed.X);
  }
  cout<<ans1<<" "<<ans2<<endl;
	return 0;
}
