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
const ll MAXN = 3e5;
ll n,m,a,b,idx,cnt;
vector<ll> e[100000];
vector<pair<ll,ll> > edges;
bool am[740][100000] = {};
map<ll,ll> id_tab;
int main()
{
  IOS();
  cin>>n>>m;
  ll sqrtm = ll(sqrt(m));
  while(m--){
    cin>>a>>b;
    e[a].pb(b);
    e[b].pb(a);
    edges.pb({a,b});
  }

  REP(i,n) {
    sort(e[i].begin(),e[i].end());
    if(e[i].size()>sqrtm){
      for(auto v:e[i])am[idx][v]=1;
      id_tab[i] = idx++;
    }
  }

  for(auto ed:edges){
    if(e[ed.X].size()>sqrtm)swap(ed.X,ed.Y);
    if(e[ed.Y].size()>sqrtm){
      ll id = id_tab[ed.Y];
      for(auto v:e[ed.X]){
        if(am[id][v])cnt++;
      }
    } else {
      vector<ll> tmp;
      auto it = set_intersection(e[ed.X].begin(),e[ed.X].end(),e[ed.Y].begin(),e[ed.Y].end(),tmp.begin());
      cnt+=it-tmp.begin();
    }
  }

  cout<<cnt/3<<endl;


	return 0;
}
