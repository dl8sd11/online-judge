#include <bits/stdc++.h>
using namespace std;
typedef int ll;
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
const ll MAXN = 1e5 + 7;
ll n,m;
ll ans = 0;
vector<ll> e[MAXN];
ll dis[MAXN];
ll sz[MAXN];
ll dp[MAXN];
void init(){
  REP(i,MAXN)dis[i]=i,sz[i]=1;
}
ll find(ll x){
  if(dis[x]!=x)dis[x]=find(dis[x]);
  return dis[x];
}
void merge(ll x,ll y){
  if(sz[x=find(x)]<sz[y=find(y)])swap(x,y);
  dis[y]=x;
  sz[x] = sz[x] + sz[y];
}
ll dfs(ll id,ll root){
  if(dp[id]!=-1)return dp[id];
  ll ret = 0;
  for(auto v:e[id]){
    if(v==root)break;
    ret = max(ret,dfs(v,id));
  }
  ans = max(ans,ret+1);
  return dp[id] = ret + 1;
}
ll pos2id(ll i,ll j){
  return j+i*m;
}
int main()
{
  IOS();
  cin>>n>>m;
  ll f[n][m];
  MEM(dp,-1);
  init();
  REP(i,n)REP(j,m)cin>>f[i][j];


  REP(i,n){
    vector<pair<ll,ll> > far;
    REP(j,m)far.pb({j,f[i][j]});
    sort(ALL(far),[](const pair<ll,ll> &a,const pair<ll,ll> &b){return a.Y<b.Y;});
    REP(j,m-1)if(far[j].Y==far[j+1].Y)merge(pos2id(i,far[j].X),pos2id(i,far[j+1].X));
  }

  REP(j,m){
    vector<pair<ll,ll> > far;
    REP(i,n)far.pb({i,f[i][j]});
    sort(ALL(far),[](const pair<ll,ll> &a,const pair<ll,ll> &b){return a.Y<b.Y;});
    REP(i,n-1)if(far[i].Y==far[i+1].Y)merge(pos2id(far[i].X,j),pos2id(far[i+1].X,j));
  }

  REP(i,n){
    vector<pair<ll,ll> > far;
    REP(j,m)far.pb({j,f[i][j]});
    sort(ALL(far),[](const pair<ll,ll> &a,const pair<ll,ll> &b){return a.Y<b.Y;});
    REP(j,m-1){
      if(far[j].Y<far[j+1].Y){
        e[find(pos2id(i,far[j+1].X))].pb(find(pos2id(i,far[j].X)));
      }
    }
  }

  REP(j,m){
    vector<pair<ll,ll> > far;
    REP(i,n)far.pb({i,f[i][j]});
    sort(ALL(far),[](const pair<ll,ll> &a,const pair<ll,ll> &b){return a.Y<b.Y;});
    REP(i,n-1){
      if(far[i].Y<far[i+1].Y){
        e[find(pos2id(far[i+1].X,j))].pb(find(pos2id(far[i].X,j)));
      }
    }
  }
  REP(i,n*m){
    if(find(i)==i)dfs(i,i);
  }
  REP(i,n*m)debug(find(i));
  REP(i,n*m)debug(dp[i]);

  cout<<ans<<endl;
	return 0;
}

//Github is great
