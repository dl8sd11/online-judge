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
const ll MAXN = ll(2e5) +7;
ll a[MAXN],sz[MAXN];
vector<pii> ei;
vector<pii> e[MAXN];
ll n,m,x,y,wi;
stack<ll> ts;
ll ans[MAXN];
queue<ll> BFS;
bool visit[MAXN];
ll w[MAXN];
ll solve(ll v) {
  ll ret = a[v];
  for (auto u:e[v]) {
    ret = min(ret,ans[u.X]+2*u.Y);
  }
  return ret;
}
int main(){
  IOS();
  cin>>n>>m;
  REP (i,m) {
    cin>>x>>y>>wi;
    ei.pb({x,y});
    w[i] = wi;
  }
  REP1 (i,n) cin>>a[i];
  ll idx = ei.size();
  while(ei.size()) {
    pii tmp = ei.back();
    ei.pop_back();
    if (a[tmp.X]>a[tmp.Y]) {
       e[tmp.X].pb(mp(tmp.Y,w[--idx]));
       sz[tmp.Y]++;
    } else {
      e[tmp.Y].pb(mp(tmp.X,w[--idx]));
       sz[tmp.X]++;
    }
  }
  pary(sz+1,sz+n);
  REP1 (i,n) {
    if (sz[i]==0) {
      if (e[i].size()==0) {
        ans[i] = a[i];
      } else {
        BFS.push(i);
      }
      visit[i]=1;
    }
  }
  debug(BFS.size());
  debug(BFS.front());
  while(BFS.size()) {
    ll tmp = BFS.front();
    BFS.pop();
    ts.push(tmp);
    for (auto v:e[tmp]) {
      ll vr = v.X;
      sz[vr]--;
      if (sz[vr]<=0&&visit[vr]==0)BFS.push(vr);
    }
  }
  while(ts.size()) {
      ans[ts.top()]=solve(ts.top());
      ts.pop();
  }
  REP1(i,n)cout<<ans[i]<<' ';

	return 0;
}
