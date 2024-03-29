#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <utility>
#include <sstream>
#include <stack>
#include <queue>
#include <set>
#include <map>
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

const ll MOD=1000000007;
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAXN=5e3+5;
const ll MAXLG=__lg(MAXN)+2;

ll f,r,tx,ty;
vector<ll> e[MAXN];
ll pt[MAXN]; //stack
ll *ptr = pt;

ll id[MAXN],low[MAXN],bcc[MAXN],t=0;
vector<pii> bridge;
ll bcc_deg[MAXN];
void dfs(ll nd,ll par){
  id[nd] = low[nd] = ++t;
  ptr++;
  (*ptr) = nd;
  for(ll v:e[nd]){
    if(!id[v])dfs(v,nd);
    if(v!=par)cmin(low[nd],low[v]);
  }
  if(low[nd]==id[nd]){
    if(nd!=par)bridge.emplace_back(nd,par);
    ll temp;
    do{
      bcc[temp=*ptr] = nd;
      ptr--;
    }while(temp!=nd);
  }
}
/********** Main()  function **********/
int main()
{
  IOS();
  cin>>f>>r;
  while(r--){
    cin>>tx>>ty;
    e[tx].pb(ty);
    e[ty].pb(tx);
  }
  dfs(1,1);
  pary(bcc+1,bcc+f+1);
  for(auto p:bridge){
    bcc_deg[p.X]++;
    bcc_deg[p.Y]++;
  }
  ll sum = 1;
  REP1(i,f)if(bcc_deg[i]==1)sum++;
  debug(sum);
  cout<<(sum+1)/2<<endl;
	return 0;
}
