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
const ll MAXN = int(1e6) + 7;
int t,n;
int a[MAXN];
int cmd,x,y;
struct Node {
  int l,r;
  Node *lc, *rc; //[)
  int data;
  Node (int li,int ri,Node *lci,Node *rci,int di):l(li),r(ri),lc(lci),rc(rci),data(di){}
};
Node *build(int l,int r) {
  if (r-l==1) {return new Node(l,r,NULL,NULL,a[l]);}
  Node *now =  new Node(l,r,build(l,(l+r)/2),build((l+r)/2,r),0);
  now->data = min(now->lc->data,now->rc->data);
  return now;
}
int query(int l,int r,Node *now) {
  if (l==now->l&&r==now->r)return now->data;
  int mid = (now->l+now->r)/2;
  if (r<=mid) return query(l,r,now->lc);
  if (l>=mid) return query(l,r,now->rc);
  return min(query(l,mid,now->lc),query(mid,r,now->rc));
}
void mody (int l,int data,Node *now) {
  if (l==now->l&&l+1==now->r) {
    now->data = data;
    return;
  }
  if (l>=(now->l+now->r)/2) {
    mody(l,data,now->rc);
    now->data = min(now->lc->data,now->rc->data);
  } else {
    mody(l,data,now->lc);
    now->data = min(now->lc->data,now->rc->data);
  }
}
int main()
{
  IOS();
  cin>>t>>n;
  REP (i,n) cin>>a[i];
  Node *root = build(0,n);
  while (t--) {
    cin>>cmd>>x>>y;
    if (cmd == 1) cout<<query(x,y+1,root)<<endl;
    else mody(x,y,root);
  }
	return 0;
}
