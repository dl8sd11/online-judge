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
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
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
const ll MAXN = (ll)1e6 + 3;
ll n,a,b,c;
ll x[MAXN];
ll f(ll w){return a*w*w+b*w+c;}
deque<pair<ll,ll>> dqu;
ll dp[MAXN],s[MAXN];
/********** Main()  function **********/
ll calc(pair<ll,ll> line,ll w) {
  return line.X*w+line.Y;
}
pair<ll,ll> getfront(ll w){
  while(dqu.size()>=2) {
    if(calc(dqu[0],w)<calc(dqu[1],w))dqu.pop_front();
    else break;
  }
  return dqu.front();
}
double intersect(pair<ll,ll> l1,pair<ll,ll> l2) {return double(l2.Y-l1.Y)/double(l1.X-l2.X);}
void addline(ll idx) {
  pair<ll,ll> nl = {-2*a*s[idx],dp[idx]+f(s[idx])-2*b*s[idx]};
  while(dqu.size()>=2) {
      ll sz = (ll)dqu.size();
      double d1 = intersect(dqu[sz-1],dqu[sz-2]),d2=intersect(dqu[sz-2],nl);
      debug(d1,d2);
      if(intersect(dqu[sz-1],dqu[sz-2])>=intersect(dqu[sz-2],nl))dqu.pop_back();
      else break;
  }
  dqu.push_back(nl);
}
int main()
{
  IOS();
  cin>>n>>a>>b>>c;
  REP1(i,n)cin>>x[i];
  dqu.push_front({0,c});
  dp[0] = 0,s[0] = 0;
  REP1(i,n) {
    debug(dqu);
    s[i] = x[i]+s[i-1];
    debug(calc(getfront(s[i]),s[i]));
    dp[i] = f(s[i])-c+calc(getfront(s[i]),s[i]);
    addline(i);
    debug(dp[i]);
  }
  cout<<dp[n]<<endl;
	return 0;
}
