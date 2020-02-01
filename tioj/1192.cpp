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
#define SZ(i) ll(i.size())
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
const ll MAXN = 500003;
ll t;
ll n,l,tmp;
vector<ll> po[MAXN];
vector<ll> na[MAXN];
vector<ll> edge[1003];
ll vis[1003];
void addEdge(ll u,ll v){
  edge[u].pb(v);
  edge[v].pb(u);
}

bool DFS(ll nd,ll color){
  bool ret = 0;
  vis[nd] = color;
  for(ll v:edge[nd]){
    if(!vis[v])ret |= DFS(v,3-color);
    if(vis[v]==color)return true;
  }
  return ret;
}
/********** Main()  function **********/
int main()
{
  IOS();
  cin>>t;
  while(t--){
    cin>>n>>l;

    REP(i,MAXN)po[i].clear(),na[i].clear();
    REP(i,1003)edge[i].clear();

    REP(i,n){
      while(cin>>tmp&&tmp)po[tmp].pb(i);
      while(cin>>tmp&&tmp)na[tmp].pb(i);
    }

    REP(i,MAXN){
      REP(j,SZ(po[i]))REP(k,SZ(na[i]))addEdge(po[i][j],na[i][k]);
    }

    MEM(vis,0);
    bool flag = 0;
    REP(i,1003){
      if(vis[i])continue;
      flag |= DFS(i,1);
    }

    if(flag)cout<<"No"<<endl;
    else cout<<"Yes"<<endl;
  }
	return 0;
}
