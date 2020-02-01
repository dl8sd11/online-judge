#include <bits/stdc++.h>
using namespace std;
typedef int ll;
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
  node *l,*r;
  ll key, pri;
}*root;

node *merge(node *a,node *b){
  if(!a||!b)return a?a:b;
  if(a->pri < b->pri){
    a->r =merge(a->r,b);
    return a;
  } else {
    b->l = merge(a,b->l);
    return b;
  }
}

void split(node *o,node *&a,node *&b,ll k){
  if(!o){
    a=0,b=0;
    return;
  }
  if(o->key < k){
    a = o;
    split(o->r,a->r,b,k);
  } else {
    b = o;
    split(o->l,a,b->l,k);
  }
}

void insert(ll val){
  if(!root){
    root = new node{0,0,val,rand()};
    return;
  }
  node *a=0,*b=0;
  split(root,a,b,val);
  root = merge(a,merge(new node{0,0,val,rand()},b));
}

void query(ll val){
    node *a=0,*b=0,*aa,*bb;
    split(root,a,b,val);
    debug(a,b);
    aa =a,bb = b;
    if(a)while(a->r)a=a->r;
    if(b)while(b->l)b=b->l;
    root = merge(aa,bb);
    if(!a) {
      cout<<b->key<<endl;
      return;
    }
    if(!b){
      cout<<a->key<<endl;
      return;
    }

    if(abs(a->key-val)>abs(b->key-val)){
      cout<<b->key<<endl;
    } else if (abs(a->key-val) < abs(b->key-val)){
      cout<<a->key<<endl;
    } else {
      cout<<a->key<<" "<<b->key<<endl;
    }
}

void erase(ll val){
  node *a=0,*b=0,*c=0;
  split(root,a,b,val);
  split(b,b,c,val+1);

  debug(a,b,c);
  node *tmp = b;
  b = merge(b->l,b->r);
  delete tmp;

  root = merge(a,merge(b,c));
}
int main()
{
  IOS();
  srand(time(0));
  ll n;
  cin>>n;
  ll x;
  string cmd;
  root = 0;
  REP(i,n){
    cin>>cmd>>x;
    if(cmd[0]=='i'){
      insert(x);
    }else if(cmd[0]=='d'){
      erase(x);
    } else {
      query(x);
    }
  }
	return 0;
}
