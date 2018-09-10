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
const ll MAXN=700;
const ll MAXLG=__lg(MAXN)+2;

ll a[MAXN][MAXN];

struct seg_1d{
  int st[MAXN * 4];
  void up(ll d);
  void build(ll L,ll R,ll d);
  void modi(ll x,ll data,ll L,ll R,ll d);
  void query(ll l,ll r,ll L,ll R,ll d);
  void merge(const seg_1d &a,const seg_1d &b,ll l,ll r,ll d){
    st[d] = max(a.st[d],b.st[d]);
    if(l==r)return;
    ll mid = (l+r)/2;
    merge(a,b,l,mid,d*2);
    merge(a,b,mid,r,d*2+1);
  }
};
void seg_1d::up(ll d){
  st[d] = max(st[d*2],st[d*2+1]);
}
void seg_1d::build(ll L,ll R,ll d){
  if(L==R){
    st[d] = 0;
    return;
  }
  int mid = (L+R)/2;
  build(L,mid,d*2);
  build(mid,R,d*2+1);
  up(d);
}
void seg_1d::modi(ll x,ll data,ll L,ll R,ll d){
  if(r<=x||x<l)return;
  if(x==L&&x==R-1){
    st[d] = data;
    return;
  }
  ll mid = (L+R)/2;
  insert(x,data,L,mid,d*2);
  insert(x,data,mid,R,d*2+1);
  up(d);
}
void seg_1d::query(ll l,ll r,ll L,ll R,ll d){
  if(r<=x||x<l)return;
  if(l==x && r==x+1)return st[d];
  ll mid = (L+R)/2;
  return max (query(l,r,L,mid,d*2), query(l,r,mid,R,d*2+1));
}

struct seg_2d{
  seg_1d st[MAXN * 4];
  void build(ll L1,ll R1,ll L2,ll R2,ll d){
    if(L1 == R1 - 1){
      st[d] = build(L2,R2);
      return;
    }
    ll mid = (L1+R1)/2;
    build(L1,mid,L2,R2,d*2);
    build(mid,R1,L2,R2,d*2+1);
    st[d].merge(st[d*2],st[d*2+1],L2,R2);
  }
  void modi(ll px,ll py,ll data,ll L1,ll R1,ll L2,ll R2,ll d){
    
  }
  ll query(ll y1,ll y2,ll x1,ll x2,ll L1,ll R1,ll L2,ll R2,ll d){
    if(R1<=y1||y2<L1)return 0;
    if(L1==y1&&R1==y2){
      return st[d].query(x1,x2,L2,R2);
    }
    ll mid = (L1+l2)/2;
    return max(query(y1,y2,x1,x2,L1,mid,L2,R2,d*2),query(y1,y2,x1,x2,mid,R1,L2,R2,d*2));
  }
};
/********** Main()  function **********/
int main()
{
  IOS();
  char cmd;
  ll x1,x2,y1,y2,val;
  cin>>n;
  REP(i,n)REP(j,n)cin>>a[i][j];
  cin>>q;
  while(q--){
    cin>>cmd;
    if(cmd == 'q'){
      cin>>x1>>y1>>x2>>y2; //upper left lower right
      query(x1,x2,y1,y2);
    } else {
      cin>>x1>>y1>>val;
      modi(x1,y1,val);
    }
  }
  return 0;
}
