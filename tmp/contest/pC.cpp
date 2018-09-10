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
const ll MAXN = 2002;
/********** Main()  function **********/
int n,m,x,y;
struct edge{
  ll X;ll Y;ll Z;
};
vector<edge> e[MAXN];
vector<edge> re  [MAXN];
vector<bool> ism(MAXN);
vector<ll> d(MAXN,INF);
int main()
{
  IOS();
  cin>>n>>m>>x>>y;
  d[x] = 0;
  REP(i,m){
    ll st,ed,cost,mag;
    cin>>st>>ed>>cost>>mag;
    e[st].pb({ed,cost,mag});
    re[ed].pb({st,cost,mag});
  }
  queue<pii> q;
  q.push({x,0});
  while(q.size()){
    ll now = q.front().X;
    ll nowm = q.front().Y;
    if(nowm){
      for(ll i=0;i<re[now].size();i++){
        edge v = re[now][i];
        if(d[v.X] >= d[now] + v.Y){
          q.push({v.X,!v.Z});
          d[v.X] = d[now] + v.Y;
        }
      }
    } else {
      for(ll i=0;i<e[now].size();i++){
        edge v = e[now][i];
        if(d[v.X] >= d[now] + v.Y){
          q.push({v.X,v.Z});
          d[v.X] = d[now] + v.Y;
        }
      }
    }

    q.pop();
  }
  if(d[y]==INF)cout<<-1<<endl;
  else cout<<d[y]<<endl;
	return 0;
}
