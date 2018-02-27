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
struct node{
  int l,r;
  node *lc,*rc;
  pair<int,int> d;
  bool tag;
  void pull() {
    if(lc&&rc) {
      lc->push();
      rc->push();
      d.X = lc->d.X+rc->d.X;
      d.Y = lc->d.Y+rc->d.Y;
    }
  }
  void push() {
    if(tag) {
      d.X +=d.Y;
      d.Y=0;
      if(lc&&rc) {
        rc->tag =1;
        lc->tag = 1;
      }
    }
    tag=0;
  }
  node(int li,int ri,node *lci,node *rci,pair<int,int> di):l(li),r(ri),lc(lci),rc(rci),d(di),tag(0){pull();}
};
void printTree(node *nd) {
  debug(nd->l,nd->r);
  debug(nd->d);
  if(nd->lc) {
    printTree(nd->lc);
    printTree(nd->rc);
  }
}
node *build(int l,int r){
  if(l==r-1)return new node(l,r,0,0,{1,0});
  int mid = (l+r)/2;
  return new node(l,r,build(l,mid),build(mid,r),{-1,-1});
}
void add(int l,int r,node *nd) {
  nd->push();
  if(l==nd->l&&r==nd->r) {
    swap(nd->d.X,nd->d.Y);
    return;
  }
  int mid=(nd->l+nd->r)/2;
  if(l>=mid) add(l,r,nd->rc);
  else if(r<=mid) add(l,r,nd->lc);
  else {
    add(l,mid,nd->lc);
    add(mid,r,nd->rc);
  }
  nd->pull();
}
int query(int l,int r,node *nd) {
  nd->push();
  if(l==nd->l&&r==nd->r) {
    return nd->d.X;
  }
  int mid=(nd->l+nd->r)/2;
  if(l>=mid)  return query(l,r,nd->rc);
  else if(r<=mid) return query(l,r,nd->lc);
  else return query(l,mid,nd->lc) + query(mid,r,nd->rc);
}
void clear(int l,int r,node *nd){
  if(nd->tag)return;
  if(l==nd->l&&r==nd->r) {
    debug(l,r);
    nd->tag=1;
    return;
  }
  int mid=(nd->l+nd->r)/2;
  if(l>=mid) clear(l,r,nd->rc);
  else if(r<=mid) clear(l,r,nd->lc);
  else {
    clear(l,mid,nd->lc);
    clear(mid,r,nd->rc);
  }
  nd->pull();
}
int n,m,x,y;
string cmd;
int main()
{
  IOS();
  cin>>n>>m;
  node *root = build(0,n);
  printTree(root);
  while(m--) {
    cin>>cmd>>x>>y;
    if(cmd[0]=='T') {
      add(x-1,y,root);
    } else if(cmd[0]=='C') {
      debug(cmd);
      cout<<query(x-1,y,root)<<endl;
    } else {
      clear(x-1,y,root);
    }
    printTree(root);
  }
	return 0;
}
