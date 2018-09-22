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
const ll MAXN=1e5+5;
const ll MAXLG=__lg(MAXN)+2;


#define f(x) ((x*x+c)%n)

ll mypow(ll base,ll exp,ll md){
  if(exp==1)return base % md;
  ll hlf = mypow(base,exp>>1,md);
  return (exp&1?hlf*hlf%md*base%md:hlf*hlf%md);
}
bool miller_rabin(ll n,ll a){
  if(n<2)return false;
  ll u = n-1,t = 0;
  while(!(u&1))u>>=1,t++;
  ll x = mypow(a,u,n);
  if(x==1||x==n-1)return true;
  for(ll i=0;i<t-1;i++){
    x = x*x%n;
    if(x==1)return false;
    if(x==n-1)return true;
  }
  return false;
}
bool isprime(ll n){
  vector<ll> a = {2,3,5,7,11,13,17,19,23,29,31,37};
  bool ret = 1;
  for(ll i=0;i<a.size();i++){
    if(a[i]!=n)ret &= miller_rabin(n,a[i]);
  }
  return ret;
}


ll pollard_rho(ll n,ll c){
  ll a0 = rand()%n;
  ll x = a0,y = a0;
  while(true){
    x = f(x);y = f(f(y));
    if(x==y)return n;
    ll d = __gcd(abs(x-y),n);
    if(d>1&&d<n)return d;
  }
  return -1;
}

ll factor;
void factorize(ll n){

  if(n==1)return;
  if(isprime(n)){
    factor = max(factor,n);
    return;
  }
  ll d = n;

  for(ll c=0;d==n;++c){
    d = pollard_rho(n,c);
  }


  factorize(d);
  factorize(n/d);
}

/********** Main()  function **********/
int main()
{
  IOS();
  ll t,n;
  while(cin>>n&&n){
    factor = 1;
    factorize(n);

    if(factor==1||factor==n)cout<<-1<<endl;
    else cout<<factor<<endl;
  }
  return 0;
}
