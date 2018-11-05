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


const ll MOD=1000000007;
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAXN=100003;
const ll MAXLG=__lg(MAXN)+2;
ll n,q;
ll a[MAXN];

struct node{
  ll l,r;
  node *lc,*rc;
  ll data,tag;
};

node *build(ll l,ll r){
  if(r==l+1)return new node{l,r,0,0,a[l],0};
  ll mid = (l+r)/2;
  return new node{l,r,build(l,mid),build(mid,r),0,0};
}

void add(ll l,ll r,ll val,node *nd){
  debug(l,r,val);
  if(l==nd->l && r == nd->r){
    nd->tag += val;
    return;
  }
  ll mid = (nd->l + nd->r) /2;
  if(l>=mid)add(l,r,val,nd->rc);
  else if(r<=mid)add(l,r,val,nd->lc);
  else {
    add(l,mid,val,nd->lc);
    add(mid,r,val,nd->rc);
  }
}

ll query(ll x,node *nd){
  if(nd->l == nd->r - 1)return nd->data + nd->tag;
  ll mid = (nd->l + nd->r) / 2;
  if(x>=mid) return nd->tag + query(x,nd->rc);
  else return nd->tag + query(x,nd->lc);
}
/********** Main()  function **********/
int main()
{
  IOS();
  cin>>n;
  REP(i,n)cin>>a[i];
  cin>>q;
  node *root = build(0,n);
  ll cmd,u,v,b;
  while(q--){
    cin>>cmd;
    if(cmd == 1){
      cin>>u>>v>>b;
      add(u-1,v,b,root);
    } else {
      cin>>u;
      cout<<query(u-1,root)<<endl;
    }
  }
  return 0;
}
