#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
typedef pair<ll,ll> pii;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
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
const ll MAXN = 3e5;
ll n,m,s,e,f;
ll a,b,c1,d,c2;
ll cost;
vector<pii > edge[107];
int main()
{
  IOS();
  ll t;
  cin>>t;
  while(t--){
    cin>>n>>m>>s>>e>>f;
    REP(i,107)edge[i].clear();
    REP(i,m){
      cin>>a>>b>>c1>>d>>c2;
      if(f>d)cost = c2 * (f-d) + c1 * d;
      else cost = c1 * f;
      debug(a,b,cost);
      edge[a].pb({b,cost});
    }
    ll dis[107] = {};
    REP(i,107)dis[i]=INF;
    bool visited[107] = {};
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    dis[s] = 0;
    visited[s] = 1;
    pq.push({0,s});
    REP(i,n){

      ll found = INF;
      while(pq.size()&&visited[found=pq.top().Y])pq.pop();
      if(found==INF)break;
      visited[found] = 1;
      debug(found);
      for(auto v:edge[found]){
        if(!visited[v.X]&&dis[found] + v.Y<dis[v.X]){
          dis[v.X] = dis[found] + v.Y;
          debug("push",dis[v.X],v.X);
          pq.push({dis[v.X],v.X});
        }
      }
    }
    pary(dis+1,dis+5);
    assert(dis[e]!=INF);
    cout<<dis[e]<<endl;
  }
	return 0;
}
