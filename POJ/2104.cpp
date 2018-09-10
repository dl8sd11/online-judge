#include <iostream>
#include <assert.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <utility>
#include <sstream>
#include <stack>
#include <queue>
#include <set>
#include <map>
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


const ll MOD=1000000007;
const ll MAXN=1e5+5;

struct node{
  node *lc,*rc;
  ll l,r;
  ll data;
  node(node *lci,node *rci,ll li,ll ri,ll datai):lc(lci),rc(rci),l(li),r(ri),data(datai){}
  void pull(){
    data = 0;
    if(lc)data += lc->data ;
    if(rc)data += rc->data;
  }
};

node *build(ll l,ll r){
  if(r==l+1)return new node(0,0,l,r,0);
  ll mid = (l+r)/2;
  return new node(build(l,mid),build(mid,r),l,r,0);
}


node *add(ll l,node *nd){
  nd = new node(*nd);
  if(l==nd->l&&l==nd->r-1){
    nd->data++;
    return nd;
  }
  ll mid = (nd->l + nd->r)/2;
  if(l>=mid) nd->rc = add(l,nd->rc);
  else nd->lc = add(l,nd->lc);
  nd->pull();
  return nd;
}
ll tmp;
ll query(node *nd1,node *nd2,ll kt){
  if(nd1->l==nd1->r-1)return nd1->l;
  tmp = nd2->lc->data - nd1->lc->data;
  if(tmp >= kt){
    return query(nd1->lc,nd2->lc,kt);
  } else {
    return query(nd1->rc,nd2->rc,kt-tmp);
  }

}

ll n,m,x,y,k;
ll a[MAXN],b[MAXN],c[MAXN];
node *root[MAXN];
/********** Main()  function **********/
int main()
{
  IOS();
  cin>>n>>m;
  REP(i,n)cin>>a[i],c[i]=a[i];

  sort(a,a+n);
  ll nn = unique(a,a+n)-a;

  REP(i,n){
    b[i] = lower_bound(a,a+nn,c[i])-a;
  }

  root[0] = build(0,nn);

  for(ll i=0;i<n;i++){
    root[i+1] = add(b[i],root[i]);
  }


  for(ll i=0;i<m;i++){
    cin>>x>>y>>k;
    x--;

    cout<<a[query(root[x],root[y],k)]<<endl;
  }

	return 0;
}
