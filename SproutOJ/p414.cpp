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
typedef pair<ll, ll> pii;
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
const ll MAXN = 6e5+7;
ll n,m,t1,t2,k1,k2;
vector<pii> e[MAXN];
ll p[MAXN];
ll s[MAXN];
vector<ll> ans;
ll dfs(ll nd,ll par){
  if(nd>n){ //user
    pii ms = {0,0};
    ll rsum = -p[nd];
    vector<pii> posnd;
    for(auto v:e[nd]){
      if(v.X==par)continue;
      ll tmp = dfs(v.X,nd);
      if(tmp>=0)posnd.pb(v);
      if(tmp<0)rsum += tmp;
      else if(tmp>ms.Y)ms.X = v.X,ms.Y=tmp;
    }
    debug(nd,rsum,ms.Y);
    if(-rsum>ms.Y) {
      for(auto v:posnd){
        ans.pb(v.Y);
        debug(v);
      }
      return rsum;
    } else {
      for(auto v:posnd){
        if(v.X!=ms.X){
          ans.pb(v.Y);
          debug(v);
        }
      }
      return ms.Y-rsum;
    }

  }else{  //power
    ll ret = p[nd];
     for(auto v:e[nd]){
       if(v.X==par)continue;
       ll tmp = dfs(v.X,nd);
       if(tmp>=0) {
         ans.pb(v.Y);
         debug(v);
       }
       else ret+=tmp;
     }
     if(ret<0)return -1e18;
     return ret;
  }
}
int main()
{
  IOS();
  cin>>n>>m;
  REP1(i,n+m-1){
    cin>>t1>>k1>>t2>>k2;
    e[(t1-1)*n+k1].pb({(t2-1)*n+k2,i});
    e[(t2-1)*n+k2].pb({(t1-1)*n+k1,i});
  }
  REP1(i,n+m)cin>>p[i];
  cout<<"DEE"<<dfs(1,1)<<endl;
  debug(ans);
	return 0;
}


// 2 2
// 1 1 2 1
// 2 1 2 2
// 2 2 1 2
// 1 1
// 2 1
