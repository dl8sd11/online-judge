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
ll n,x,y,m,k;
double ans;
vector<pi > p;
vector<pi > hull(1000);
pi operator -(const pi &a,const pi &b){return mp(a.X-b.X,a.Y-b.Y);}
ll operator *(const pi &a,const pi &b){return a.X*b.Y - a.Y*b.X;}
double dis(const pi &a,const pi &b){return sqrt((a.X-b.X)*(a.X-b.X) + (a.Y-b.Y)*(a.Y-b.Y));}
bool cmp(const pi &a,const pi &b)//排序方法
{
    if(a.X == b.X)
        return a.Y < b.Y;
    return a.X < b.X;
}
/********** Main()  function **********/
int main()
{
  IOS();
  while(cin>>n&&n!=0){
    p.clear();
    REP(i,n)cin>>x>>y,p.pb({x,y});
    if(n==1){
      cout<<0<<endl;
      continue;
    }
    sort(ALL(p),cmp);
    m = 0;
    REP(i,n){
      while(m>1&&(hull[m-1]-hull[m-2])*(p[i]-hull[m-2])<=0)m--;
      hull[m++] = p[i];
    }
    k=m;
    for(ll i=n-2;i >=0; i--) {
      while(m>k&&(hull[m-1]-hull[m-2])*(p[i]-hull[m-2])<=0)m--;
      hull[m++] = p[i];
    }

    if(n > 1)m--;

    debug(hull);
    debug(m);

    ans = 0;

    for(int i = 1; i < m; i++)
        ans+=dis(hull[i],hull[i-1]);
    ans+=dis(hull[m-1],hull[0]);

    if(n==2)ans/=2.0;
    cout<<fixed<<setprecision(2)<<ans<<'\n';
  }
	return 0;
}
