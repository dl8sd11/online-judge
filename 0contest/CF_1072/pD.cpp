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
const ll MAXN=2e3+5;
const ll MAXLG=__lg(MAXN)+2;

ll n,k;
char grid[MAXN][MAXN];
ll dp[MAXN][MAXN];
ll lp = -1;
vector<pair<ll,ll> > lh;
vector<string> ans;
ll rk[MAXN][MAXN];
vector<pair<ll,ll> > st;

ll getbst(ll i,ll j){
  if(i==n-1)return rk[i][j+1];
  else if(j==n-1)return rk[i+1][j];
  return min(rk[i+1][j],rk[i][j+1]);
}
bool cmp (const pair<ll,ll> &a,const pair<ll,ll> &b){
  if(grid[a.X][a.Y] != grid[b.X][b.Y]) {
    return grid[a.X][a.Y] < grid[b.X][b.Y];
  }
  else {
    return getbst(a.X,a.Y) < getbst(b.X,b.Y);
  }
}
void build(){
  rk[n-1][n-1] = 1;
  for(ll i=2*n-3;i>=0;i--){
    st.clear();
    for(ll j=0;j<n;j++){
      if(i-j<0 || i-j >= n)continue;
      st.emplace_back(i-j,j);
    }

    sort(ALL(st),cmp);
    debug(st);
    ll rt = 0;
    for(ll j=0;j<SZ(st);j++){
      if(j==0 || grid[st[j].X][st[j].Y] != grid[st[j-1].X][st[j-1].Y] || getbst(st[j].X,st[j].Y) != getbst(st[j-1].X,st[j-1].Y)) rt++;

      rk[st[j].X][st[j].Y] = rt;
    }
  }
}
void solve(ll i,ll j){
  string ret;
  while(i<n-1 || j<n-1){
    if(i==n-1) ret += grid[i][++j];
    else if(j==n-1) ret += grid[++i][j];
    else {
      if(rk[i][j+1] < rk[i+1][j]) {
        ret += grid[i][++j];
      } else {
        ret += grid[++i][j];
      }
    }
  }
  ans.emplace_back(ret);
}
/********** Main()  function **********/
int main()
{
  IOS();
  cin>>n>>k;
  REP(i,n) {
    REP(j,n) {
      cin>>grid[i][j];
      dp[i][j] = (grid[i][j]=='a') + max((i==0?0:dp[i-1][j]),(j==0?0:dp[i][j-1]));
    }
  }
  build();



  REP(i,n) {
    REP(j,n){
      if(i+j+1 <= dp[i][j] + k) {
        if(i+j+1 > lp) {
          lh.clear();
          lp = i+j+1;
          lh.emplace_back(i,j);
        } else if(i+j+1 == lp) {
          lh.emplace_back(i,j);
        }
      }
    }
  }

  if(lh.size() == 0){
    assert(grid[0][0] != 'a');
    assert(k==0);
    cout<<grid[0][0];
    solve(0,0);
    for(ll i=0;i<SZ(ans[0]);i++)cout<<ans[0][i];
    cout<<endl;
    return 0;
  }

  for(auto p:lh){
    solve(p.X,p.Y);
  }

  sort(ALL(ans));
  REP(i,lh[0].X+lh[0].Y+1)cout<<'a';
  for(ll i=0;i<SZ(ans[0]);i++)cout<<ans[0][i];
  cout<<endl;
  return 0;
}
