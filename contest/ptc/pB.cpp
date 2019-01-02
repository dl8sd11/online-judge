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

ll t,die[MAXN];
ll n,a[MAXN];
ll lpre[MAXN];
ll rpre[MAXN];
ll pre[MAXN];
vector<ll> facv;
vector<ll> ans;
ll left(ll idx,ll day){
  auto first = lower_bound(ALL(facv),idx-day);
  auto last = lower_bound(ALL(facv),idx);
  if(last == facv.begin() || first == facv.end()) return 0;
  last--;
  ll sum = day * (pre[idx]-pre[(*first)-1]);
  ll rpresum = (rpre[idx]-rpre[(*first)-1]);
  ll presum = (pre[idx]-pre[(*first)-1]);
  return  presum;
}
ll right(ll idx,ll day){
  auto first = lower_bound(ALL(facv),idx);
  auto last = upper_bound(ALL(facv),idx+day);
  last--;
  if(first == facv.end()) return 0; // no right
  if(*first - idx > day) return 0;
  ll sum = day * (pre[*last]-pre[idx]);
  ll lpresum = (lpre[*last]-lpre[idx-1]);
  ll presum = (pre[*last]-pre[idx-1]);
  return  presum;
}
/********** Main()  function **********/
int main()
{
  IOS();
  cin>>t;
  while(t--){
    cin>>n;
    facv.clear();
    pre[0] = 0;
    lpre[0] = 0;
    rpre[0] = 0;
    REP1(i,n) {
      cin>>a[i];
      pre[i] = pre[i-1];
      lpre[i] = lpre[i-1];
      rpre[i] = rpre[i-1];
      if(a[i]<0){
        facv.emplace_back(i);
        pre[i] += a[i];
        lpre[i] += a[i]*i;
        rpre[i] += a[i]*(n-i+1);
      }
    }

    debug(left(1,1));
    debug(right(1,1));
    MEM(die,0);
    REP1(i,n){
      if(a[i] > 0) {
        ll L = 0,R = 10000003;
        while(L<R-1){
          ll mid = (L+R)/2;
          if(left(i,mid) + right(i,mid) + a[i] > 0 )L = mid;
          else R = mid;
        }
        die[i] = L+1;
      }
    }

    ll mx = -1;
    ans.clear();
    pary(die+1,die+n+1);
    REP1(i,n){
      if(a[i] < 0 )continue;
      if(die[i] > mx){
        ans.clear();
        ans.pb(i);
        mx = die[i];
      } else if(die[i] == mx){
        ans.pb(i);
      }
    }

    cout<<ans.size();
    REP(i,SZ(ans)){
      cout<<" "<<ans[i];
    }
    cout<<endl;
  }
  return 0;
}
