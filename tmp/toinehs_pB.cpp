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
const ll MAXN = (ll)1e5 + 7;
const ll MAXlg = __lg(MAXN) + 2;
struct node{
  ll l,r;
  node *lc,*rc;
  ll data;
  node(ll li,ll ri,node *lci,node *rci,ll datai):l(li),r(ri),lc(lci),rc(rci),data(datai){}
  void pull() {
    data = (lc?lc->data:0) + (rc?rc->data:0);
  }
};
ll n,K,t;
ll a[MAXlg][MAXN],k[MAXN],d[MAXN],tin[MAXN],tout[MAXN];
node *root[MAXN];
vector<ll> e[MAXN];
void mody(node *p,ll pos){
  if(pos==p->l&&pos==p->r-1) {
    p->data++;
    return;
  }
  ll mid = (p->l+p->r)/2;
  if(pos>=mid) {
    if(!p->rc) p->rc = new node(mid,p->r,0,0,0);
    mody(p->rc,pos);
  }
  else {
    if(!p->lc) p->lc = new node(p->l,mid,0,0,0);
    mody(p->lc,pos);
  }
  p->pull();
}
ll query(node *p,ll l,ll r) {
  if(!p)return 0;
  if(l==p->l&&r==p->r)return p->data;
  ll mid = (p->l+p->r)/2;
  if(l>=mid) return query(p->rc,l,r);
  else if(r<=mid) return query(p->lc,l,r);
  else return query(p->lc,l,mid)+query(p->rc,mid,r);
}
void DFS(ll idx,ll par) {
  a[0][idx] = par;
  d[idx] = d[par]+1;
  tin[idx]=t++;
  for(int i=1;i<MAXlg;i++) {
    a[i][idx] = a[i-1][a[i-1][idx]];
  }
  for(auto u:e[idx]) {
    DFS(u,idx);
  }
  tout[idx]=t++;
}
/********** Main()  function **********/
int main()
{
  IOS();
  cin>>n>>K;
  REP1(i,n) {
    cin>>a[0][i];
    cin>>k[i];
    e[a[0][i]].pb(i);
  }
  debug(n);
  DFS(0,0);
  debug(d[0]);
  debug(tin[0],tout[0]);
  root[1] = new node(0,n*2+5,0,0,0);
  mody(root[1],tin[0]);
  REP1(i,n) {

    if(!root[d[i]])root[d[i]] = new node(0,n*2+5,0,0,0);
    mody(root[d[i]],tin[i]);
    ll rd = d[i]-ceil(k[i]/2.0);
    if(rd<=0)rd=1;
    ll td = i;
    for(ll j=MAXlg-1;j>=0;j--) {
      if(d[a[j][td]]>=rd)td = a[j][td];
    }
    cout<<query(root[d[i]-1],tin[td],tout[td]+1)-1<<endl;
  }

	return 0;
}
