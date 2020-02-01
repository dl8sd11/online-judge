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
const ll MAXN=2e5+5;
const ll MAXLG=__lg(MAXN)+2;

ll n,x,y,tmp;
char inst[MAXN];
ll cl[MAXN],cr[MAXN],cu[MAXN],cd[MAXN];
ll clo,cro,cuo,cdo;
ll cnt;

bool solve(ll idx,ll len){
  if(len == -1)return false;
  clo = (idx?cl[idx-1]:0) + cl[n-1] - (idx+len-1 >=0 ?cl[idx+len-1]:0);
  cro = (idx?cr[idx-1]:0) + cr[n-1] - (idx+len-1 >=0 ?cr[idx+len-1]:0);
  cuo = (idx?cu[idx-1]:0) + cu[n-1] - (idx+len-1 >=0 ?cu[idx+len-1]:0);
  cdo = (idx?cd[idx-1]:0) + cd[n-1] - (idx+len-1 >=0 ?cd[idx+len-1]:0);
  cnt = abs(x - (cro - clo)) + abs(y - (cuo - cdo));
  if(cnt <= len && (len - cnt)%2 == 0) return true;
  return false;
}

/********** Main()  function **********/
int main()
{
  IOS();
  cin>>n;
  REP(i,n)cin>>inst[i];
  cin>>x>>y;

  REP(i,n){
    if(inst[i]=='R')cr[i]++;
    else if(inst[i]=='L')cl[i]++;
    else if(inst[i]=='U')cu[i]++;
    else if(inst[i]=='D')cd[i]++;

    if(i!=0){
      cr[i] += cr[i-1];
      cl[i] += cl[i-1];
      cu[i] += cu[i-1];
      cd[i] += cd[i-1];
    }
  }

  ll L = -1, R = n+1;
  while(L < R-1){
    bool ret = 0;
    ll mid = (L+R)/2;
    for(ll i=0;i+mid <= n;i++){
      ret |= solve(i,mid);
    }
    if(ret)R = mid;
    else L = mid;
  }
  if(R == n+1) cout<<-1<<endl;
  else cout<<R<<endl;
  return 0;
}
