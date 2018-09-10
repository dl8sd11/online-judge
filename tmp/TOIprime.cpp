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
const ll MAXN = 1000000;
ll n;
ll dp[15][15];
bool sieve[MAXN];
vector<ll> prime;
void  linear_sieve(){
  sieve[0]=1;
  sieve[1]=1;
  for(int i=2;i<MAXN;i++) {
    if(!sieve[i])prime.pb(i);
    for(int j=0;prime[j]*i<MAXN;j++) {
      sieve[prime[j]*i]=1;
      if(i%prime[j]==0)break;
    }
  }
}
/********** Main()  function **********/
int main()
{
  IOS();
  cin>>n;
  linear_sieve();
  ll cnt = 0;
  for(auto v:prime) {
    if(n%v==0) n/=v,cnt++;
    if(n==1)break;
  }
  debug(cnt);
  dp[1][1] = 1;
  for(int i=2;i<=cnt;i++) {
    dp[1][i] = 1;
    for(int j=2;j<i;j++) {
      dp[j][i] = (dp[j-1][i-1] + (dp[j][i-1]*j)%MOD)%MOD;
    }
    dp[i][i] = dp[i-1][i-1];
  }
  ll ans = 0;
  for(int i=1;i<=cnt;i++) {
    ans += dp[i][cnt];
  }
  cout<<ans<<endl;
	return 0;
}
