#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) ll(i.size())
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
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

template<class T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template<class T> using MaxHeap = priority_queue<T>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

const ll MOD=1000000007;
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAXN=1e5+5;
const ll MAXLG=__lg(MAXN)+2;

struct state{
  ll b,l,d;
  state(ll bb,ll li,ll di):b(bb),l(li),d(di){}
  state(){l=-1;}
};
class cmp{
public:
  bool operator()(const state &a,const state &b){return a.d>b.d;}
};
ll n,m,k;
ll f,t,d;

ll ans;
ll dis[32768][15];
state from[32768][15];
bool vis[32768][15];
ll mt,tmp,st;
vector<pii> edge[MAXN];
vector<ll> ans_vec;
priority_queue<state,vector<state>,cmp > dij;
vector<ll> print_state(state input){
  vector<ll> vec;
  state now = input;
  while(from[now.b][now.l].l!=-1){
    vec.eb(now.l);
    now = from[now.b][now.l];
  }
  vec.eb(now.l);
  reverse(ALL(vec));
  return vec;
}
/********** Main()  function **********/
int main()
{
  IOS();

  MEM(dis,INF);
  MEM(vis,0);

  ans = INF;
  cin>>n>>m;
  REP(i,m){
    cin>>f>>t>>d;
    edge[f].eb(t,d);
    edge[t].eb(f,d);
  }
  cin>>k;
  REP(i,k){
    cin>>st;
    if(i==0)dis[1<<st][st]=0,dij.emplace(1<<st,st,0);
    mt += 1<<st;
  }

  while(dij.size()){
    while(dij.size()&&vis[dij.top().b][dij.top().l])dij.pop();
    if(dij.empty())break;
    state nd = dij.top();dij.pop();

    vis[nd.b][nd.l] = 1;
    if((nd.b&mt)==mt){
      if(nd.d==ans){
        vector<ll> tmpv = print_state(nd);
        if(lexicographical_compare(ALL(tmpv),ALL(ans_vec)))ans_vec = tmpv;
      } else if(nd.d<ans) ans_vec = print_state(nd);
      cmin(ans,nd.d);
    }
    for(auto e:edge[nd.l]){
      if(dis[nd.b|(1<<e.X)][e.X] > dis[nd.b][nd.l] + e.Y){
        dis[nd.b|(1<<e.X)][e.X] = dis[nd.b][nd.l] + e.Y;
        from[nd.b|(1<<e.X)][e.X] = nd;
        dij.emplace(nd.b|(1<<e.X),e.X,dis[nd.b|(1<<e.X)][e.X]);
      }
    }
  }


  cout<<"Minimum travel distance: "<<ans<<endl;
  cout<<"Travel route: ";
  for(auto nd:ans_vec){
    cout<<nd<<' ';
  }
  cout<<endl;
	return 0;
}
