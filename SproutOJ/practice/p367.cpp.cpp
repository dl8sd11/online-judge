#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define X first
#define Y second
typedef pair<ll, ll> pi;
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

const ll INF = (ll)1e18 + 7;
const ll MOD = 1000000007;
const ll MAXN = 3e5;
ll n,q,a[MAXN];

struct node{
  ll l,r;
  node *lc,*rc;
  ll data,tag;
};

node *build(ll l,ll r){
  node *ret = new node;
  ll mid = (l+r)/2;
  if (r==l+1) *ret = {l,r,0,0,a[l],0};
  else {
    *ret = {l,r,build(l,mid),build(mid,r),0,0};
    ret->data = max(ret->lc->data,ret->rc->data);
  }
  return ret;
}

void add(ll l,ll r,ll x,node *nd){
  if(l==nd->l&&r==nd->r){
    nd->tag += x;
    return;
  }
  ll mid = (nd->l+nd->r)/2;
  if(r<=mid)add(l,r,x,nd->lc);
  else if(l>=mid)add(l,r,x,nd->rc);
  else add(l,mid,x,nd->lc),add(mid,r,x,nd->rc);
  nd->data = max(nd->lc->data + nd->lc->tag , nd->rc->data + nd->rc->tag);
}

ll query(ll l,ll r,node *nd){

  if(l==nd->l&&r==nd->r)return nd->data + nd->tag;
  ll mid = (nd->l+nd->r)/2;
  if(r<=mid) return query(l,r,nd->lc) + nd->tag;
  else if(l>=mid) return query(l,r,nd->rc) + nd->tag;
  else return max(query(l,mid,nd->lc),query(mid,r,nd->rc)) + nd->tag;
}

int main()
{
  IOS();
  cin>>n>>q;
  REP(i,n)cin>>a[i];
  node *root = build(0,n);

  ll cmd,l,r,x;
  while(q--){
    cin>>cmd;
    if(cmd==1){
      cin>>l>>r>>x;
      add(l-1,r,x,root);
    } else {
      cin>>l>>r;
      cout<<query(l-1,r,root)<<endl;
    }
  }
	return 0;
}
