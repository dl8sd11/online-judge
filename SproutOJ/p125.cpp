#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
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
const ll MOD = 10000019;
const ll MAXN = ll(1e6)+3;
int n,a[MAXN];
void merge_part(int l,int r) {
  int mid = (l+r)/2;
  int d[MAXN];
  int idx = l;
  int idxl = l;
  int idxr = mid;
  for(int i=l;i<r;i++)d[i]=a[i];
  while(idxl<mid) {
    while(idxr<r&&d[idxr]<d[idxl]) {
      a[idx++] = d[idxr++];
    }
    a[idx++] =d[idxl++];
  }
}
int merge(int l,int r) {
  if(r==l+1) return 0;
  ll ret = 0;
  ll mid = (l+r)/2;
  ret+=(merge(l,mid)+merge(mid,r))%MOD;
  int idxl=mid,idxr=r;
  int sum = 0;
  while(--idxr>=mid) {
    while(idxl>l&&a[idxl-1]>a[idxr]) {
      sum+=a[--idxl];
      sum%=MOD;
    }
    ret+=a[idxr]*(mid-idxl)+sum;
    ret%=MOD;
  }
  merge_part(l,r);
  debug(l,r,ret);
  return ret;
}
int main()
{
  IOS();
  cin>>n;
  REP(i,n)cin>>a[i];
  cout<<merge(0,n)<<endl;
	return 0;
}
