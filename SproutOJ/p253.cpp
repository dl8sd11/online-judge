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
const ll MAXN = 6000;
ll n;
ll a[MAXN],f[MAXN],g[MAXN],p[MAXN];
int main()
{
  IOS();
  cin>>n;
  REP(i,n)cin>>a[i];
  reverse(a,a+n);
  pary(a,a+n);
  f[0] = 1;
  g[0] = 1;
  p[0] = 0;
  REP(i,n){
    ll mx = 0;
    g[i] = 1;
    p[i] = i;
    REP(j,i){
        if(a[j]>=a[i]){
          if(f[j]>mx){
            mx = f[j];
            p[i] = j;
            g[i] = g[j];
          } else if(f[j]==mx) {
            g[i] += g[j];
            p[i] = j;
            g[i] %= MOD;
          }
        }
    }
    f[i] = mx + 1;
  }
  pary(f,f+n);
  pary(g,g+n);
  pary(p,p+n);
  ll ans = 0;
  ll cnt = 0;
  REP(i,n) {
    if(f[i]>ans){
      ans = f[i];
      cnt = g[i];
    } else if(f[i]==ans){
      cnt += g[i];
      cnt %= MOD;
    }
  }
  cout<<ans<<endl;
  cout<<cnt<<endl;
  ll start = -1;
  for(ll i=n-1;i>=0;i--){
    if(f[i] == ans) {
      start = i;
      break;
    }
  }

  while(p[start]!=start){
    cout<<n-start<<' ';
    start = p[start];
  }
  cout<<n-start<<endl;
	return 0;
}
