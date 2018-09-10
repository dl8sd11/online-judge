#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define SZ(i) (ll)(i.size())
#define ALL(_a) _a.begin(),_a.end()
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define X first
#define Y second
typedef pair<ll, ll> pi;
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

const ll INF = (ll)1e18 + 7;
const ll MOD = 1000000007;
const ll MAXN = 100;
struct Edge{ll from,to,flow,cap,rev;};
vector<Edge> G[MAXN];
ll s,t,n,dis[MAXN],cur[MAXN];
void init(){
  REP(i,MAXN)G[i].clear();
}
void add_edge(ll u,ll v,ll cap){
  G[u].pb({u,v,0,cap,SZ(G[v])});
  G[v].pb({v,u,0,0,SZ(G[u])-1});
}

ll dfs(ll u,ll cap){
  if(u==t||!cap)return cap;
  for(ll &i=cur[u];i<SZ(G[u]);i++){
    Edge &e = G[u][i];
    if(dis[e.to]==dis[u]+1 && e.cap!=e.flow){
      ll df = dfs(e.to,min(cap,e.cap - e.flow));
      if(df){
        e.flow += df;
        G[e.to][e.rev].flow -= df;
        return df;
      }
    }
  }
  dis[u] = -1;
  return 0;
}
bool bfs(){
  MEM(dis,-1);
  queue<ll> q;
  q.push(s);dis[s] = 0;
  while(!q.empty()){
    ll u = q.front();q.pop();
    for(auto e: G[u]){
      if(dis[e.to]==-1 && e.cap!=e.flow){
        q.push(e.to);
        dis[e.to] = dis[u] + 1;
      }
    }
  }
  return dis[t] != -1;
}
ll Dinic(){
  ll flow = 0,df;
  while(bfs()){
    MEM(cur,0);
    while(df = dfs(s,INF)){
      flow += df;
    }
  }
  return flow;
}
/********** Main()  function **********/
int main()
{
  IOS();
  ll T,m,u,v,cap;
  cin>>T;
  REP1(tn,T){
    cin>>n>>m;
    s = 0,t = n-1;
    init();
    REP(i,m){
      cin>>u>>v>>cap;
      add_edge(u-1,v-1,cap);
    }
    cout<<"Case "<<tn<< ": "<< Dinic()<<endl;
  }
	return 0;
}
