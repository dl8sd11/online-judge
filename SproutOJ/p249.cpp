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
const ll MAXN = int(1e5) + 3;
ll n,q;
ll a[MAXN];
struct node{
  ll l,r;
  node *lc, *rc;
  ll dl,dr,dx,da;
  node(ll li,ll ri,node *lci,node *rci,ll dli,ll dri,ll dxi,ll dai):l(li),r(ri),lc(lci),rc(rci),dl(dli),dr(dri),dx(dxi),da(dai){}
};
struct data{
  ll dl,dr,dx,da;
  data(){}
  data(ll dli,ll dri, ll dxi,ll dai):dl(dli),dr(dri),dx(dxi),da(dai){}
};
node *build(ll l,ll r) {
  if (r==l+1) return new node(l,r,NULL,NULL,a[l],a[l],a[l],a[l]);
  ll mid = (l+r)/2;
  node *ret = new node(l,r,0,0,0,0,0,0);
  ret->lc = build(l,mid);
  ret->rc = build(mid,r);
  ret->da = ret->lc->da + ret->rc->da;
  ret->dl = max(ret->lc->dl,ret->lc->da+ret->rc->dl);
  ret->dr = max(ret->rc->dr,ret->rc->da+ret->lc->dr);
  ret->dx = max(ret->lc->dx,ret->rc->dx); // check
  ret->dx = max(ret->dx,ret->lc->dr+ret->rc->dl);
  return ret;
}
data query(ll l,ll r,node *now) {
  debug(mp(l,r));
  if (l==now->l&&r==now->r) return data(now->dl,now->dr,now->dx,now->da);
  ll mid = (now->l+now->r)/2;
  if (r<=mid) return query(l,r,now->lc);
  if (l>=mid) return query(l,r,now->rc);
  data ldata, rdata, ret;
  ldata = query(l,mid,now->lc);
  rdata = query(mid,r,now->rc);
  ret.da = ldata.da+rdata.da;
  ret.dl = max(ldata.dl,ldata.da+rdata.dl);
  ret.dr = max(rdata.dr,rdata.da+ldata.dr);
  ret.dx = max(ldata.dx,rdata.dx); // check
  ret.dx = max(ret.dx,ldata.dr+rdata.dl);
  return ret;
}
int main()
{
  IOS();
  cin>>n>>q;
  REP (i,n)cin>>a[i];
  node *root = build(0,n);
  REP (i,q) {
    ll l,r;
    cin>>l>>r;
    ll ans = query(l-1,r,root).dx;
    debug(ans);
    if (ans < 0) ans = 0;
    cout<<ans<<endl;
  }
	return 0;
}
