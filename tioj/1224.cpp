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
const ll MAXN = (ll) 1e6 + 7;
const ll INF = (ll)1e18 + 7;
const ll MOD = 1000000007;
struct edge{
  int x,d,u;
  bool tag;
};
int ST[MAXN*5],tg[MAXN*5];
void mody(int l,int r,int L,int R,int id,int data){
  if(l==L&&r==R){tg[id]+=data;return;}
  int mid=(L+R)/2;
  //tg[id*2]=tg[id],tg[id*2+1]=tg[id],tg[id]=0;
  if(l>=mid)mody(l,r,mid,R,id*2+1,data);
  else if(r<=mid)mody(l,r,L,mid,id*2,data);
  else mody(l,mid,L,mid,id*2,data),mody(mid,r,mid,R,id*2+1,data);
  ST[id] = (tg[2*id]?mid-L:ST[id*2])+(tg[id*2+1]?R-mid:ST[id*2+1]);
}
bool cmp(const edge &a,const edge &b){return a.x<b.x;}
int n;
edge e[200003];
/********** Main()  function **********/
int main()
{
  IOS();
  cin>>n;
  REP(i,n) {
    cin>>e[i*2].x>>e[i*2+1].x>>e[i*2].d>>e[i*2].u;
    e[i*2+1].u = e[i*2].u;
    e[i*2+1].d = e[i*2].d;
    e[i*2].tag = !(e[i*2+1].tag=0);
  }
  sort(e,e+n*2,cmp);
  int last = e[0].x;
  ll ans = 0;
  REP(i,n*2) {
    debug(ST[1]);
    debug(e[i].x,e[i].u,e[i].d,e[i].tag);
    ans+=ll(ST[1])*(e[i].x-last);
    mody(e[i].d,e[i].u,0,MAXN,1,ll(e[i].tag)*2-1);
    last = e[i].x;
  }
  cout<<ans<<endl;
	return 0;
}
