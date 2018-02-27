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

/********** Main()  function **********/
string s;
ll n,k,ans=0;
ll cnt[26];
ll tg[26];
ll jei[100003];
ll jeir[100003];
vector<pair<char,ll>> h;
bool cmp(const pair<char,ll> &a,const pair<char,ll> &b) {return a.Y<b.Y;}
ll myexp(ll x,ll y) {
  if(y==0)return 1;
  if(y==1)return x;
  ll tmp = myexp(x,y/2);
  tmp = (tmp*tmp)%MOD;
  return (y&1)?(tmp*x)%MOD:tmp%MOD;
}
ll solve(ll x,ll y) {
  if(0==x)return 1;
  if(y==0)return 1;
  return (jei[x]*jeir[x-y])%MOD;
}
int main()
{
  IOS();
  cin>>s;
  jei[0]=1;
  REP1(i,100002) jei[i]=(jei[i-1]*i)%MOD;
  REP(i,100003) jeir[i] = myexp(jei[i],MOD-2);
  for(ll i=0;i<10;i++) debug(jeir[i]);
  for(auto c:s) tg[c-'a']++;
  pary(tg,tg+26);
  cin>>n>>k;
  char c;
  ll hi;
  REP(i,n) {
    cin>>c>>hi;
    h.pb({c,hi});
  }
  sort(ALL(h),cmp);
  ll idx2=-1;
  for(ll idx1=0;idx1<n;cnt[h[idx1++].X-'a']--) {
    for(ll i=idx2+1;i<n;i++) {
      if (h[i].Y-h[idx1].Y<=k)idx2=i,cnt[h[i].X-'a']++;
      else break;
    }
    ll tm = 1;
    bool flag =0;
    REP(i,26) {
      if(tg[i]>cnt[i])flag=1;
    }
    if(flag)continue;
    REP(i,26) {
      if(tg[i]==0)continue;
      if(i==h[idx1].X-'a') {
        tm*=(tg[i]*solve(cnt[i]-1,tg[i]-1))%MOD;
      } else {
        tm*=solve(cnt[i],tg[i]);
      }
      tm %= MOD;
      debug(tm);
    }
    debug(idx1);
    debug(tm);
    ans = (ans+tm)%MOD;
  }
  cout<<ans<<endl;
	return 0;
}
