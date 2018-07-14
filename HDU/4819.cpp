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
const ll MAXN = 900;
ll t,n,q,case_no,x,y,L;
ll pic[MAXN][MAXN];
struct Nodey{
  ll l,r,mx,mn;
  Nodey *lc,*rc;
};
struct Nodex{
  ll l,r;
  Nodex *lc,*rc;
  Nodey *rooty;
  Nodey *buildy(ll _l,ll _r){
    if(_l==_r-1)return new Nodey{_l,_r,-INF,INF,0,0};
    ll mid = (_l+_r)/2;
    return new Nodey{_l,_r,-INF,INF,buildy(_l,mid),buildy(mid,_r)};
  }
  ll query_min(ll _l,ll _r,Nodey *nd){
    if(_l==nd->l&&_r==nd->r)return nd->mn;
    ll mid = (nd->l+nd->r)/2;
    if(_l>=mid)return query_min(_l,_r,nd->rc);
    if(_r<=mid)return query_min(_l,_r,nd->lc);
    return min(query_min(_l,mid,nd->lc),query_min(mid,_r,nd->rc));
  }
  ll query_max(ll _l,ll _r,Nodey *nd){
    if(_l==nd->l&&_r==nd->r)return nd->mx;
    ll mid = (nd->l+nd->r)/2;
    if(_l>=mid)return query_max(_l,_r,nd->rc);
    if(_r<=mid)return query_max(_l,_r,nd->lc);
    return max(query_max(_l,mid,nd->lc),query_max(mid,_r,nd->rc));
  }
  void modi(ll _y,ll val,Nodey *nd){
    if(nd->l==nd->r-1) {
      assert(nd->l==_y);
      nd->mx=val;
      nd->mn=val;
      return;
    }
    ll mid = (nd->l+nd->r)/2;
    if(_y>=mid) modi(_y,val,nd->rc);
    else if(_y<=mid) modi(_y,val,nd->lc);
    nd->mx =max(nd->lc->mx,nd->rc->mx);
    nd->mn =min(nd->lc->mn,nd->rc->mn);
  }
}*root;
Nodex *build(ll l,ll r){
  Nodex *ret;
  if(l==r-1){
    ret = new Nodex{l,r,0,0,0};
    ret->rooty = ret->buildy(0,n);
  } else {
    ll mid = (l+r)/2;
    ret = new Nodex{l,r,build(l,mid),build(mid,r),0};
    ret->rooty = ret->buildy(0,n);
  }
  return ret;
}
ll query_min(ll x1,ll x2,ll y1,ll y2,Nodex *nd){
  debug(x1,x2,y1,y2,nd->l,nd->r);
  if(x1==nd->l&&x2==nd->r)return nd->query_min(y1,y2,nd->rooty);
  ll mid = (nd->l+nd->r)/2;
  if(x1>=mid)return query_min(x1,x2,y1,y2,nd->rc);
  if(x2<=mid)return query_min(x1,x2,y1,y2,nd->lc);
  return min(query_min(x1,mid,y1,y2,nd->lc),query_min(mid,x2,y1,y2,nd->rc));
}
ll query_max(ll x1,ll x2,ll y1,ll y2,Nodex *nd){
  if(x1==nd->l&&x2==nd->r)return nd->query_max(y1,y2,nd->rooty);
  ll mid = (nd->l+nd->r)/2;
  if(x1>=mid)return query_max(x1,x2,y1,y2,nd->rc);
  if(x2<=mid)return query_max(x1,x2,y1,y2,nd->lc);
  return max(query_max(x1,mid,y1,y2,nd->lc),query_max(mid,x2,y1,y2,nd->rc));
}
void modi(ll _x,ll _y,ll val,Nodex *nd){
  debug(_x,_y,val,nd->l,nd->r);
  nd->modi(_y,val,nd->rooty);
  if(nd->l==nd->r-1) return;
  ll mid = (nd->l+nd->r)/2;
  if(_x>=mid) modi(_x,_y,val,nd->rc);
  else if(_x<=mid) modi(_x,_y,val,nd->lc);

}
/********** Main()  function **********/
int main()
{
  IOS();
  while(cin>>t){
    while(t--){
        cout<<"Case #"<<case_no<<":\n";
        cin>>n;
        REP(i,n)REP(j,n)cin>>pic[i][j];
        root = build(0,n);
        REP(i,n)REP(j,n)modi(i,j,pic[i][j],root);
        cin>>q;
        while(q--){
          cin>>L>>x>>y;
          if(L==1){
            cin>>L;
            modi(x,y,L,root);
          } else {
            ll x2,y2;
            cin>>x2>>y2;
            ll a = query_min(x,x2+1,y,y2+1,root);
            ll b = query_max(x,x2+1,y,y2+1,root);
            debug(a,b);
          }
          // cin>>x>>y>>L;
          // x--,y--;
          // ll x1 = max(x-L/2,0LL);
          // ll x2 = min(x+L/2,n-1);
          // ll y1 = max(y-L/2,0LL);
          // ll y2 = min(y+L/2,n-1);
          // ll a = query_min(x1,x2+1,y1,y2+1,root);
          // ll b = query_max(x1,x2+1,y1,y2+1,root);
          // debug(a,b);
          // modi(x,y,(a+b)/2,root);
          // cout<<(a+b)/2<<'\n';
        }
    }
  }
	return 0;
}
