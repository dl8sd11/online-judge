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

ll n;
ll X,Y,c1,c2,n1,n2;
ll ceilDiv(ll x,ll y){
  ll ret = x/y;
  if(ret*y < x)ret++;
  return ret;
}
ll extGCD(ll a,ll b,ll &x,ll &y){
  if(b==0){
    x = 1;
    y = 0;
    return a;
  }
  ll r = extGCD(b,a%b,x,y);
  ll t = y;
  y = x - (a/b)*y;
  x = t;
  return r;
}
bool swped;
pii bst;
/********** Main()  function **********/
int main()
{
  IOS();
  while(cin>>n&&n){
    swped = 0;
    bst = {-1,-1};
    cin>>c1>>n1>>c2>>n2;
    ll gcd = extGCD(n1,n2,X,Y);
    debug(gcd,X,Y);

    if(n%gcd!=0)cout<<"failed"<<endl;
    else{
      X *= n/gcd;
      Y *= n/gcd;
      if(X<Y){
        swped = 1;
        swap(n1,n2);
        swap(c1,c2);
        swap(X,Y);
      }
      ll tms = ceilDiv(abs(Y),(n1/gcd));
      Y += tms*(n1/gcd);
      X -= tms*(n2/gcd);
      if(X < 0){
        cout<<"failed"<<endl;
      } else {
        bst = {X,Y};
        tms = X / (n2/gcd);
        X -= tms*(n2/gcd);
        Y += tms*(n1/gcd);
        debug(mp(X,Y));
        debug(X*c1+Y*c2);
        debug(bst);
        debug(bst.X*c1+bst.Y*c2);
        if(X*c1+Y*c2 < bst.X*c1+bst.Y*c2)bst = {X,Y};
        if(swped){
          cout<<bst.Y<<" "<<bst.X<<endl;
        } else {
          cout<<bst.X<<" "<<bst.Y<<endl;
        }
      }
    }
  }
  return 0;
}
