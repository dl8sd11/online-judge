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
const ll MAXN = int(1e5)+7;
int n;
int m;
int delay[MAXN];
int dp[MAXN];
int x,y;
vector<int> Mlast[MAXN];
vector<int> e[MAXN];
vector<int> ein[MAXN];
vector<int> zin;
set<int> ans;
void addElement (int idx) {
  debug(idx);
  debug(Mlast[idx]);
  if (ans.count(idx)) return;
  else ans.insert(idx);
  for (auto el:Mlast[idx]) {
    addElement(el);
  }
}
void solve(int idx) {
  int ret = 0;
  for (auto v:ein[idx]) {
    //debug(v);
    if (dp[v]==-1)solve(v);
    if (dp[v]>ret) {
      Mlast[idx].clear();
      Mlast[idx].pb(v);
      ret = dp[v];
    } else if (dp[v]==ret) {
      Mlast[idx].pb(v);
    }
  }
  ret += delay[idx];
  dp[idx] = ret;
  debug(dp[idx]);
}
int main()
{
  IOS();
  cin>>n>>m;
  MEM(dp,-1);
  REP1 (i,n) {
    cin>>delay[i];
  }
  REP (i,m) {
    cin>>x>>y;
    e[x].pb(y);
    ein[y].pb(x);
  }
  REP1 (i,n) {
    if (!e[i].size()) {
      zin.pb(i);
      solve(i);
    }
  }
  debug(zin);
  int maxv = 0;
  REP1 (i,n) maxv = max(maxv,dp[i]);
  REP1 (i,n) if (dp[i]==maxv) {
    debug(i);
    addElement(i);
  }
  cout<<ans.size()<<endl;
	return 0;
}
