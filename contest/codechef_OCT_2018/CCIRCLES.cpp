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
const ll MAXN=1e3+5;
const ll MAXLG=__lg(MAXN)+2;
const ll MAXR=2e6+7;

ll n,q;
ll x[MAXN],y[MAXN],R[MAXN];
ll k;
ll seg[MAXR*2];

pair<ll,ll> dis(ll i,ll j){
  ll disq = (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
  ll l = 0,r = 1e9;
  while(l<r-1){
    ll mid = (l+r)/2;
    if(mid*mid<=disq)l = mid;
    else r = mid;
  }
  if(l*l == disq)return make_pair(l,l);
  else return make_pair(l,r);
}

void add(ll l,ll r){
  debug(l,r);
  for(l+=MAXR,r+=MAXR;l<r;l>>=1,r>>=1){
    if(l&1)seg[l++]++;
    if(r&1)seg[--r]++;
  }
}

ll query(ll pos){
  ll ret = 0;
  for(pos+=MAXR;pos>=1;pos>>=1){
    ret += seg[pos];
  }
  return ret;
}
/********** Main()  function **********/
int main()
{
  IOS();
  cin>>n>>q;
  REP(i,n)cin>>x[i]>>y[i]>>R[i];
  REP(i,n){
    REP(j,i){
      pair<ll,ll> ret = dis(i,j);
      debug(ret);
      if((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])>=abs(R[i]-R[j])*abs(R[i]-R[j])){
        add(max(0LL,ret.Y-R[i]-R[j]),min(1000000LL,ret.X+R[i]+R[j])+1);
      } else {
        add(abs(R[i]-R[j])-ret.X,min(1000000LL,ret.X+R[i]+R[j])+1);
      }
    }
  }
  while(q--){
    cin>>k;
    cout<<query(k)<<endl;
  }
  return 0;
}
