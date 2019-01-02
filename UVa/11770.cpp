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
const ll MAXN=1e5+5;
const ll MAXLG=__lg(MAXN)+2;

ll t,n,m,ccnt,cur,ans,a,b;
vector<ll> edge[MAXN];
vector<ll> redge[MAXN];
vector<ll> topo;
bool vis[MAXN];
vector<ll> G[MAXN];
ll idx[MAXN];
void DFS1(ll nd){
  vis[nd] = 1;
  for(auto v:edge[nd])if(!vis[v])DFS1(v);
  topo.eb(nd);
}

void DFS2(ll nd,ll p){
  vis[nd] = 1;
  for(auto v:redge[nd]){
    if(!vis[v])DFS2(v,p);
  }
  idx[nd] = p;
}

void DFS3(ll nd){
  vis[nd] = 1;
  for(auto v:G[nd])if(!vis[v])DFS3(v);
}
/********** Main()  function **********/
int main()
{
  IOS();
  cin>>t;
  for(ll casen = 1;casen <= t;casen++){
    cin>>n>>m;
    REP1(i,n)edge[i].clear();
    REP1(i,n)redge[i].clear();
    REP(i,m)cin>>a>>b,edge[a].eb(b),redge[b].eb(a);

    MEM(vis,0);
    topo.clear();
    REP1(i,n)if(!vis[i])DFS1(i);
    MEM(vis,0);

    debug(topo);
    ccnt = 0;
    RREP(i,n-1)if(!vis[topo[i]])DFS2(topo[i],ccnt++);

    pary(idx+1,idx+n+1);
    REP(i,ccnt)G[i].clear();    
    REP1(i,n){
      for(auto v:edge[i])G[idx[i]].eb(idx[v]);
    }

    MEM(vis,0);
    ans = 0;
    REP(i,ccnt){
      if(!vis[i])DFS3(i),ans++;
    }

    cout<<"Case "<<casen<<": "<<ans<<endl;
  }
  return 0;
}
