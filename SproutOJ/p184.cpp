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
const ll MAXN = int(1e6)+7;
int n,m;
int x,y;
vector<int> e[MAXN];
int lv[MAXN];
int low[MAXN];
bool visit[MAXN];
vector<pair<int,int> > input;
map<pair<int,int>,bool> isans;
void DFS(int now,int curlv,int par) {
  lv[now] = curlv;
  low[now] = curlv;
  visit[now] = 1;
  for (auto v: e[now]) {
    if (visit[v]) {
      //parent
      if (v==par)continue;
      // back edge to descendant
      if (lv[v]>curlv)continue;
      // back edge to ancestor
      low[now]= min(low[now],lv[v]);
    } else {
      // this is a child
      DFS(v,curlv+1,now);
      low[now] = min(low[now],low[v]);
      if (low[v] == lv[v])
        isans[mp(min(v,now),max(v,now))] = 1;
    }

  }
}
int main()
{
  IOS();
  cin>>n>>m;
  REP (i,m) {
    cin>>x>>y;
    e[x].pb(y);
    e[y].pb(x);
    input.pb(mp(min(x,y),max(x,y)));
    isans[mp(min(x,y),max(x,y))] = 0;
  }
  DFS(1,0,1);
  for (auto a:input) if (isans[mp(a.X,a.Y)]) cout<<a.X<<' '<<a.Y<<endl;
	return 0;
}
