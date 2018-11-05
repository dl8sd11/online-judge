#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
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
const ll MAXN = (ll)1e5 + 7;
const ll MAXlg = __lg(MAXN)+2;
ll n,q,m,tmp;
vector<ll> s[MAXN];
vector<ll> ss[MAXN];
vector<ll> pre[MAXN];
map<pii,ll> ans;
/********** Main()  function **********/
ll f(ll l,ll r) {
  ll ret = 0;
  if(ss[l].size()>ss[r].size())swap(l,r);
  ll bl=-1,br=ss[r].size();
  debug(ss[l]);
  debug(ss[r]);
  while(br!=bl+1) {
    ll mid = (bl+br)/2;
    if(ss[l][0]>ss[r][mid])bl = mid;
    else br = mid;
  }
  for(auto u:ss[l]) {
    while(bl+1<ll(ss[r].size())&&ss[r][bl+1]<u)bl++;
    debug(u);
    if(bl==-1)ret+=pre[r][ss[r].size()-1]-u*(ss[r].size());
    else ret+=u*(bl*2+2-ss[r].size())-pre[r][bl]*2+pre[r][ss[r].size()-1];
    debug(ret);
  }
  return ret+1;
}
int main()
{
  IOS();
  cin>>n;
  REP1(i,n) {
      cin>>m;
      REP(j,m) {
        cin>>tmp;
        ss[i].pb(tmp);
      }
      sort(ALL(ss[i]));
  }
  REP1(i,n) {
    ll sum = 0;
    REP(j,ll(ss[i].size())) {
      sum+=ss[i][j];
      pre[i].pb(sum);
    }
  }
  cin>>q;
  ll li,ri;
  while(q--) {
    cin>>li>>ri;
    ll tmp2 = ans[{li,ri}];
    if(tmp2!=0)cout<<tmp2-1<<endl;
    else tmp2 = ans[{li,ri}] = f(li,ri),cout<<tmp2-1<<endl;
  }
	return 0;
}
