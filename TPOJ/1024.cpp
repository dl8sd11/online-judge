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
#define eb emplace_back
#define X first
#define Y second
#ifdef tmd
#define debug(...) do{							\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__); \
    _do(__VA_ARGS__);							\
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
const double EPS = 1e-7;
double X1,X2,X3,X4,Y1,Y2,Y3,Y4;
struct point{
  double px,py;
  point(double xx,double yy){
    px = xx;
    py = yy;
  }
  point operator - (const point &a){
    return point{px-a.px,py-a.py};
  }
  bool operator != (const point &a){
    return a.px != px || a.py != py;
  }
};

double cross(const point &a,const point &b){
  double ret = a.px * b.py - a.py*b.px;
  if (ret <= EPS && ret >= -EPS)ret = 0;
  return ret;
}
double cross2(const point &a,const point &b){
  return a.px * b.py - a.py*b.px;
}
double dot(const point &a,const point &b){
  return a.px*b.px + b.py*a.py;
}

bool btw(point &a,point &b,point &c){
  debug("HI");
  return dot(a-c,b-c) <= EPS;
}
/********** Main()  function **********/
int main()
{
  IOS();

  cin>>X1>>Y1>>X2>>Y2>>X3>>Y3>>X4>>Y4;
  point p1(X1,Y1),p2(X2,Y2),p3(X3,Y3),p4(X4,Y4);
  bool flag = 0;
  if(cross(p2-p1,p3-p1) == 0 && btw(p1,p2,p3))flag = 1;
  else if(cross(p2-p1,p4-p1) == 0 && btw(p1,p2,p4)) flag = 1;
  else if(cross(p4-p3,p2-p3) == 0 && btw(p3,p4,p2)) flag = 1;
  else if(cross(p4-p3,p1-p3) == 0 && btw(p3,p4,p1)) flag = 1;
  else if(cross2(p2-p1,p3-p1)*cross2(p1-p2,p4-p2) > 0 && cross2(p4-p3,p1-p3)*cross2(p3-p4,p2-p3) > 0)flag = 1;
  
  if(flag)cout<<"YES"<<endl;
  else cout<<"NO"<<endl;
  return 0;
}


// && cross(point(X4-X3,Y4-Y3)*point(X1-X3,Y1-X3))*(point(X3-X4,Y3-Y4)*point(X2-X4,Y2-X4)) > 0
