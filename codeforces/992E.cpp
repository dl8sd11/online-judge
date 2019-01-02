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
const ll MAXN = 2e5 + 7;
ll n,q,p,x;
ll a[MAXN];

struct sg{
  ll l, r;
  sg *lc,*rc;
  ll mx,sm;
  void pull(){
    if(lc){
      mx = max(lc->mx,rc->mx);
      sm = lc->sm + rc->sm;
    }
  }
}*root;

ll SZ(sg *nd){return nd->r - nd->l;}

sg *build(ll l,ll r){
  if(r==l+1)return new sg{l,r,0,0,a[l],a[l]};
  ll mid = (l+r)/2;
  sg *ret = new sg{l,r,build(l,mid),build(mid,r),0,0};
  ret->pull();
  return ret;
}

void modi(ll l,ll val,sg *nd){
  if(l==nd->l&&l+1==nd->r)nd->mx = nd->sm = val;
  else {
    ll mid = (nd->l+nd->r)/2;
    if(l>=mid)modi(l,val,nd->rc);
    else modi(l,val,nd->lc);
    nd->pull();
  }
}

ll findlest(ll val,sg *nd){
  debug(nd->l,nd->r,a[nd->l],val);
  if(nd->mx < val)return SZ(nd);
  if(nd->l+1==nd->r)return (a[nd->l] >= val?0:1);
  ll lres = findlest(val,nd->lc);
  if(lres < SZ(nd->lc))return lres;
  return lres + findlest(val,nd->rc);
}

ll findlest_lr(ll l,ll r,ll val,sg *nd){
  debug(l,r,nd->l,nd->r,val);
  if(l==nd->l&&r==nd->r) {
    ll tmp = findlest(val,nd);
    debug(tmp);
    return tmp;
  }
  ll mid = (nd->l+nd->r)/2;
  if(l>=mid)return findlest_lr(l,r,val,nd->rc) + SZ(nd->lc);
  else if(r<=mid) return findlest_lr(l,r,val,nd->lc);
  ll lres = findlest_lr(l,mid,val,nd->lc);
  if(lres < SZ(nd->lc))return lres;
  return findlest_lr(mid,r,val,nd->rc) + SZ(nd->lc);
}

ll qsum(ll l,ll r,sg *nd){
  if(l==nd->l&&r==nd->r)return nd->sm;
  ll mid = (nd->l+nd->r)/2;
  if(l>=mid)return qsum(l,r,nd->rc);
  else if(r<=mid) return qsum(l,r,nd->lc);
  return qsum(l,mid,nd->lc) + qsum(mid,r,nd->rc);
}
/********** Main()  function **********/
int main()
{
  IOS();
  while(cin>>n>>q){
    REP(i,n)cin>>a[i];
    root = build(0,n);
    REP(i,q){
      cin>>p>>x;
      debug(p,x);
      p--;
      modi(p,x,root);
      a[p] = x;
      if(a[0]==0){
        cout<<1<<endl;
        continue;
      }
      if(n>=2&&a[0] == a[1]) {
        cout<<2<<endl;
        continue;
      }
      ll ptr = 0;
      ll sum;
      bool flag = 0;
      while(ptr<n-1){
        debug(ptr);
        sum = qsum(0,ptr+1,root);
        debug(sum);
        ptr = findlest_lr(ptr+1,n,sum,root);
        if(ptr==n)break;
        if(qsum(0,ptr,root) == a[ptr]){
          cout<<ptr+1<<endl;
          flag = 1;
          break;
        }
      }
      if(!flag)cout<<-1<<endl;

    }
  }

	return 0;
}
