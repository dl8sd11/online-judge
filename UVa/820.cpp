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
#define debug(...) do{							\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__); \
    _do(__VA_ARGS__);							\
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
const ll MAXN=1e2+5;
const ll MAXLG=__lg(MAXN)+2;

ll n,m,s,t;
struct E{ll f,t,cap,flow,rev;};
vector<E> edge[MAXN];
ll cur[MAXN];

void init(){
  REP(i,MAXN)edge[i].clear();
}

void addEdge(ll u,ll v,ll c){
  edge[u].pb((E){u,v,c,0,SZ(edge[v])});
  edge[v].pb((E){v,u,0,0,SZ(edge[u])-1});
}
ll dis[MAXN];
bool BFS(){
  MEM(dis,-1);
  queue<ll> q;
  dis[s] = 0;
  q.push(s);
  while(!q.empty()){
    ll nd = q.front();q.pop();
    for(auto v:edge[nd]){
      if(dis[v.t]==-1&&v.cap!=v.flow){
        dis[v.t] = dis[v.f] + 1;
        q.push(v.t);
      }
    }
  }
  return dis[t]!=-1;
}

ll DFS(ll nd,ll cap){
  if(nd==t||!cap)return cap;
  for(ll &i=cur[nd];i<SZ(edge[nd]);i++){
    E &e = edge[nd][i];
    if(dis[e.t]==dis[e.f]+1&&e.flow!=e.cap){
      ll df = DFS(e.t,min(cap,e.cap - e.flow));
      if(df){
        e.flow += df;
        edge[e.t][e.rev].flow -= df;
        return df;
      }
    }
  }
  dis[nd] = -1;
  return 0;
}

ll Dinic(){
  ll flow = 0,df;
  while(BFS()){
    MEM(cur,0);
    while(df=DFS(s,INF)){
      flow += df;
    }
  }
  return flow;
}
/********** Main()  function **********/
int main()
{
  IOS();
  ll u,v,c,cnt = 0;
  while(cin>>n&&n){
    init();
    cin>>s>>t>>m;
    REP(i,m){
      cin>>u>>v>>c;
      addEdge(u,v,c);
      addEdge(v,u,c);
    }
    cout<<"Network "<<(++cnt)<<endl;
    cout<<"The bandwidth is "<<Dinic()<<"."<<endl<<endl;

  }

  return 0;
}
