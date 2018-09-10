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
#define debug(...) do{							\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__); \
    _do(__VA_ARGS__);							\
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
const ll MAXN=2e5+5;
const ll MAXLG=__lg(MAXN)+2;

ll n,m,k;
ll x,y,cur,ans;
vector<pair<ll,ll> > input;
set<ll> edge[MAXN];
ll cnt[MAXN];
bool trip[MAXN];
queue<ll> qu;
vector<ll> output;

void solve(ll u,ll V){
  pary(cnt+1,cnt+n+1);
  edge[u].erase(V);
  edge[V].erase(u);
  while(qu.size())qu.pop();
  if(cnt[u] >= k && cnt[V] >= k){
    if(cnt[u]-- == k){
      trip[u] = 0;
      ans--;
      qu.push(u);
    }
    if(cnt[V]-- == k){
      trip[V] = 0;
      ans--;
      qu.push(V);
    }
  }
    

  while(qu.size()){
    cur = qu.front();qu.pop();
    debug(cur);
    for(auto v:edge[cur]){
      if(cnt[v]-- == k){
	qu.push(v);
	ans--;
      }
      edge[v].erase(cur);
    }
    edge[cur].clear();
  }

  output.pb(ans);
}
/********** Main()  function **********/
int main()
{
  IOS();
  cin>>n>>m>>k;
  REP(i,m){
    cin>>x>>y;
    input.eb(x,y);
    edge[x].insert(y);
    edge[y].insert(x);
    cnt[x]++,cnt[y]++;
  }

  ans = n;

  REP1(i,n)if(cnt[i] < k)qu.push(i),ans--;
  while(qu.size()){
    cur = qu.front();qu.pop();
    for(auto v:edge[cur]){
      if(cnt[v]-- == k){
	qu.push(v);
	ans--;
      }
      edge[v].erase(cur);
    }
    edge[cur].clear();
  }
  
  debug(ans);
  output.eb(ans);
  for(ll i=SZ(input)-1;i>0;i--)solve(input[i].X,input[i].Y);

  for(auto it = output.rbegin();it!=output.rend();it++)cout<<*it<<" ";

  cout<<endl;
  return 0;
}
