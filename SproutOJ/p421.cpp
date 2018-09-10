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

const int INF = (int)2e9 + 7;
const ll MOD = 1000000007;
const ll MAXN = 3e5+7;
int t,n,m,l,r;
int a[MAXN];
int dp[MAXN]; //The minimun value which can hold the lingth idx
int findMin(int x){
  l = 0, r= MAXN-1;
  while (r-l>1) {
    int mid = (r+l)/2;
    if (x>=dp[mid]) l = mid;
    else r = mid;
  }
  return l+1;
}
int main()
{
  IOS();
  cin>>t;
  while (t--) {
    cin>>n>>m;
    REP (i,n) cin>>a[i];
    REP (i,MAXN) dp[i] = INF;
    dp[0] = 0;
    REP (i,n) {
      int x = findMin (a[i]);
      int x2 = findMin(a[i]*2);

      if (a[i]>=m) dp[x] = min(dp[x],a[i]);
      if (a[i]*2>=m) dp[x2] = min(dp[x2],a[i]*2);
    }
    int ans = 0;
    REP (i,MAXN) if (dp[i]<INF) ans = i;
    cout<<ans<<endl;
  }
	return 0;
}
