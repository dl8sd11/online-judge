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
ll n;
ll e[403];
ll q;
ll dis[403][403];
ll stx,sty,edx,edy;
/********** Main()  function **********/
ll real_dis(ll x,ll y,ll xx,ll yy){
  return dis[x*n+y][xx*n+yy] + e[xx*n+yy]*2 - e[x*n+y];
}
int main()
{
  IOS();
  cin>>n;
  REP(i,n)REP(j,n)cin>>e[i*n+j];

  MEM(dis,INF);
  REP(i,n*n){
    if((i+1)%n!=0)dis[i][i+1] = e[i]*2-e[i+1];
    if(i%n!=0)dis[i][i-1] = e[i]*2-e[i-1];
    if(i>=n)dis[i][i-n] = e[i]*2-e[i-n];
    if(i<n*(n-1))dis[i][i+n] = e[i]*2-e[i+n];
    dis[i][i] = 0;
  }


  REP(k,n*n){
    REP(i,n*n){
      REP(j,n*n){
        dis[i][j] = min(dis[i][j],dis[i][k]+dis[k][j]);
      }
    }
  }

  cin>>q;
  while(q--){
    cin>>stx>>sty>>edx>>edy;
    stx--,sty--,edx--,edy--;
    ll ret = INF;
    REP(i,n){
      REP(j,n){
        cmin(ret,real_dis(stx,sty,i,j)+real_dis(i,j,edx,edy)-e[i*n+j]*2);
      }
    }
    cout<<ret<<endl;
  }
	return 0;
}
