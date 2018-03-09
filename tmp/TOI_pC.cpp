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
#define SZ(a) ll(a.size())
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
const ll MAXN = (ll)2e3 + 7;
const ll MAXlg = __lg(MAXN)+2;

int last[MAXN][MAXN];
ll dp[MAXN][MAXN];
ll n,k,tmp;
vector<ll> A[10];
/********** Main()  function **********/

vector<ll> LCA(vector<ll> &a,vector<ll> &b) {
    ll maxx = 0,maxy=0;

    for(ll i=0;i<SZ(a);i++) {
      for(ll j=0;j<SZ(b);j++) {
        if(i==0||j==0) {
          if(a[i]==b[j]) {
            dp[i][j] =1;
            if(dp[i][j]>=dp[maxx][maxy])maxx=i,maxy=j;
            last[i][j] = 0;
          } else {
            if(i==0) {
              dp[i][j] = dp[i][j-1];
              last[i][j] = 1;
            } else {
              dp[i][j] = dp[i-1][j];
              last[i][j] = 2;
            }
          }
          continue;
        }
        if(a[i]==b[j]) {
          dp[i][j] = dp[i-1][j-1] + 1;
          if(dp[i][j]>=dp[maxx][maxy])maxx=i,maxy=j;
          last[i][j] = 0;
        } else {
          if(dp[i][j-1]>dp[i-1][j]) {
            dp[i][j] = dp[i][j-1];
            last[i][j] = 1;
          } else {
            dp[i][j]=dp[i-1][j];
            last[i][j] = 2;
          }
        }
      }
    }
    vector<ll> ret(n,-1);
    for(ll i=0;i<SZ(ret);i++)ret[i]=-INF;
    ll t = n;
    while(maxx>=0&&maxy>=0) {
      if(last[maxx][maxy]==0) {
        ret[--t] = a[maxx];
        maxx--,maxy--;
      } else if(last[maxx][maxy]==1) {
        maxy--;
      } else if(last[maxx][maxy]==2){
        maxx--;
      } else {
        break;
      }
    }
    debug(dp[2][5]);
    debug(dp[0][0]);
    debug(ret);
    return ret;
}
int main()
{
  IOS();

  cin>>n>>k;
  REP(u,k) REP(v,n) cin>>tmp,A[u].pb(tmp);
  REP1(i,k-1) {
    A[i] = LCA(A[i-1],A[i]);
  }
  ll ans = 0;
  for(ll i=n-1;i>=0;i--) {
    if(A[k-1][i]!=-INF)ans++;
    else break;
  }
  cout<<ans<<endl;
	return 0;
}
