#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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
const ll MAXN = ll(2e5)+7;
ll T,p,q,k,a,b,ans;
ll mty[MAXN];
bool vis[MAXN];
vector<ll> e[MAXN];
/********** Main()  function **********/
bool DFS(ll idx) {
  for(auto v:e[idx]){
    if(vis[v])continue;
    vis[v]=1;
    if(mty[v]==-1||DFS(mty[v])){
      mty[v]=idx;
      return 1;
    }
  }
  return 0;
}
void tree_sol(ll node,ll par){
  debug(node);
  for(auto v:e[node]){
    if(v==par)continue;
    tree_sol(v,node);
  }
  if(node!=par){
    if(!vis[par]&&!vis[node]) {
      vis[par]=1;
      ans++;
      debug(node,par);
    }
  }
}
int main()
{
  IOS();
  cin>>T;
  while(T--){
    cin>>p>>q>>k;
    ans = 0;
    REP(i,p+q+3)e[i].clear();
    REP(i,k)cin>>a>>b,e[a].pb(b+p),e[b+p].pb(a);
    if(k == p + q - 1){
      MEM(vis,0);
      tree_sol(1,1);
      cout<<ans<<endl;
      continue;
    }
    MEM(mty,-1);
    REP1(i,p){
      MEM(vis,0);
      if(DFS(i))ans++;
    }
    cout<<ans<<endl;
  }
	return 0;
}
