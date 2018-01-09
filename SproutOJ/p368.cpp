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
ll n, q,cmd,x,il,ir;
ll a[MAXN];
struct node {
  ll l,r;
  node *lc,*rc;
  ll d, da ,ds;
  node(ll li,ll ri,node *lci,node *rci,ll di, ll dai, ll dsi):l(li),r(ri),lc(lci),rc(rci),d(di),da(dai),ds(dsi){}
};
node *build(ll l, ll r) {
  if (r == l+1) return new node(l,r,0,0,a[l],0,0);
  ll mid = (l+r)/2;
  node *lc = build(l,mid);
  node *rc = build(mid,r);
  return new node(l,r,lc,rc,max(lc->d,rc->d),0,0);
}
ll query(ll l,ll r,node *now) {
  if (now->ds) return now->ds;
  if (now->l == l && now->r == r) return now->d+now->da;
  ll mid = (now->l+now->r)/2;
  if (r<=mid) return query(l,r,now->lc)+now->da;
  if (l>=mid) return query(l,r,now->rc)+now->da;
  return max(query(l,mid,now->lc),query(mid,r,now->rc))+now->da;
}
void add(ll l,ll r,node *now, ll data);
void sets(ll l,ll r,node *now, ll data);
void add(ll l,ll r,node *now,ll data) {
  if (now->r == now->l+1) {
    now->d += data;
    return;
  }
  ll mid = (now->l+now->r)/2;
  if (now->ds) {
    sets(now->l,mid,now->lc,now->ds);
    sets(mid,now->r,now->rc,now->ds);
    now->d = now->ds;
    now->ds = 0;
  }
  if (now->l == l && now->r == r) {
    now->da += data;
    return;
  }
  if (r<=mid) {
    add(l,r,now->lc,data);
    now->d = max(query(now->l,mid,now->lc),query(mid,now->r,now->rc));
    return;
  }
  if (l>=mid) {
    add(l,r,now->rc,data);
    now->d = max(query(now->l,mid,now->lc),query(mid,now->r,now->rc));
    return;
  }
  add(l,mid,now->lc,data);
  add(mid,r,now->rc,data);
  now->d = max(query(now->l,mid,now->lc),query(mid,now->r,now->rc));
}
void sets(ll l,ll r,node *now, ll data) {
  if (now->r == now->l+1) {
    now->d = data;
    return;
  }
  if (now->l == l && now->r == r){
    if (now->da)now->da = 0;
    now->ds = data;
    return;
  }
  ll mid = (now->l+now->r)/2;
  if (now->da) {
    add(now->l,mid,now->lc,now->da);
    add(mid,now->l,now->rc,now->da);
    now->da = 0;
  }

  if (r<=mid) {
    sets(l,r,now->lc,data);
    now->d = max(query(now->l,mid,now->lc),query(mid,now->r,now->rc));
    return;
  }
  if (l>=mid) {
    sets(l,r,now->rc,data);
    now->d = max(query(now->l,mid,now->lc),query(mid,now->r,now->rc));
    return;
  }
  sets(l,mid,now->lc,data);
  sets(mid,r,now->rc,data);
  now->d = max(query(now->l,mid,now->lc),query(mid,now->r,now->rc));
}
int main()
{
  IOS();
  cin>>n>>q;
  REP (i,n) cin>>a[i];
  node *root = build(0,n);
  debug(root);
  while (q--) {
      cin>>cmd>>il>>ir;
      if (cmd == 1) {
          cin>>x;
          add(il-1,ir,root,x);
      } else if (cmd == 2) {
          cout<<query(il-1,ir,root)<<endl;
      } else {
          cin>>x;
          sets(il-1,ir,root,x);
      }
  }
	return 0;
}
