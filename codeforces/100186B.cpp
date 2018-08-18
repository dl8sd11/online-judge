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

template<class T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template<class T> using MaxHeap = priority_queue<T>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

const ll MOD=1000000007;
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAXN=1e5+5;
const ll MAXLG=__lg(MAXN)+2;

int n,q;

struct node{
  node *l,*r;
  pii key;
  int pri,size;
  void pull(){
    size = 1;
    if(l)size += l->size;
    if(r)size += r->size;
  }
  void push(){
    if(mark){
      if(l)l->mark = mark;
      if(r)r->mark = mark;
    }
  }

}*root;

ll SIZ(ndoe *a){return a?a->size:0;}

void merge(node *a,node *b){
  if(!a||!b)return a?a:b;
  if(a->pri < b->pri){
    a->push();
    a->r = merge(a->r,b);
    a->pull();
    return a;
  } else {
    b->push();
    b->l = merge(a,b->l);
    b->pull();
    return b;
  }
}

void split(node *&o,node *a,node *b,pii k){
  if(!o){
    a = 0,b = 0;
    return;
  }
  o->push();
  if(o->key < k){
    a = o;
    split(o->r,a->r,b,k);
  } else {
    b = o;
    split(o->l,a,b->l,k);
  }
  o->pull();
}


void build(){
  REP1(i,n){
    node *tmp = new node{0,0,{0,i},rand(),1};
    if(i==1) root = tmp;
    else root =merge(root,tmp);
  }
}

void solve(int l,int r){
  node *a,*b,*c;
  split(root,a,b,{})
}
/********** Main()  function **********/
int main()
{
  IOS();


  REP(i,q){
    cin>>l>>r;
    ans = solve(l,r);
  }
	return 0;
}
