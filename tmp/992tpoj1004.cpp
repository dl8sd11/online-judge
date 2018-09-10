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
ll n,m;
ll a[MAXN];
string cmd;
ll u,v;

struct node{
  ll l,r;
  node *lc,*rc;
  ll data;
  void pull(){
    if(lc)data = min(lc->data,rc->data);
  }
};

node *build(ll l,ll r){
  if(r==l+1)return new node{l,r,0,0,a[l]};
  ll mid = (l+r)/2;
  node *tmp = new node{l,r,build(l,mid),build(mid,r),0};
  tmp->pull();
  return tmp;
}

void modify(ll x,ll val,node *nd){
  debug(nd->l,nd->r);
  if(nd->r == nd->l + 1){
    nd->data = val;
    return;
  }
  ll mid = (nd->l + nd->r) /2;
  if(x >= mid) modify(x,val,nd->rc);
  else modify(x,val,nd->lc);
  nd->pull();
}

ll query(ll l,ll r,node *nd){
  if(nd->r == nd->l + 1)return nd->data;
  ll mid = (nd->l + nd->r)/2;
  if(l>=mid) return query(l,r,nd->rc);
  else if(r<=mid) return query(l,r,nd->lc);
  else return min(query(l,mid,nd->lc),query(mid,r,nd->rc));
}

/********** Main()  function **********/
int main()
{
  IOS();
  cin>>n>>m;
  REP(i,n)cin>>a[i];
  node *root = build(0,n);
  REP(i,m){
    debug(i);
    cin>>cmd>>u>>v;
    if(cmd == "M"){
      modify(u,v,root);
    } else {
      if(u>v)swap(u,v);
      cout<<query(u,v,root)<<endl;
    }
  }
  return 0;
}
