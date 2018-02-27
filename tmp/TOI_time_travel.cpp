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
const ll MAXN = ll(2e4);
struct yearp{
  ll st,ed,data;
  yearp(ll sti,ll edi,ll datai):st(sti),ed(edi),data(datai){}
};
ll y,v[MAXN],n,a,l,r;
ll BIT[MAXN],sz[MAXN],dp[MAXN];
vector<yearp> year;
vector<ll> e[MAXN];
/********** Main()  function **********/
ll low(ll x) {return -x&x;}
ll solve(ll idx) {
  if(dp[idx]!=-1)return dp[idx];
  ll ret = 0;
  for(auto u:e[idx]) {
    ret = max(ret,solve(u)+year[u-1].data);
  }
  return dp[idx]=ret;
}
void ADD(ll pos,ll data) {
  for(;pos<=y;pos+=low(pos)) BIT[pos]+=data;
}
ll QUERY(ll pos) {
  ll ret = 0;
  for(;pos>=1;pos-=low(pos)) ret+=BIT[pos];
  return ret;
}
int main()
{
  IOS();
  cin>>y;
  REP(i,y)cin>>v[i],ADD(i+1,v[i]);
  cin>>n;
  REP(i,n) {
    cin>>l>>r;
    year.pb(yearp(l,r,QUERY(r)-QUERY(l-1)));
  }
  cin>>a;
  REP(i,a) {
    cin>>l>>r;
    e[l].pb(r);
    sz[r]++;
  }
  ll ans = 0;
  MEM(dp,-1);
  REP1(i,n) {
    if(sz[i]==0) {
      ans = max(ans,solve(i));
    }
  }
  cout<<ans<<endl;
	return 0;
}
