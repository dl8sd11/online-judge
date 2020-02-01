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

const ll MOD=998244353;
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAXN=3e5+5;
const ll MAXLG=__lg(MAXN)+2;

ll t;
ll n,m;
ll oc,ec;
vector<ll> edge[MAXN];
bool vis[MAXN];
bool odd[MAXN];
bool DFS(ll nd,bool x) {
  vis[nd] = true;
  if (x) {
    oc++;
    odd[nd] = true;
  } else {
    odd[nd] = false;
    ec++;
  }
  
  for (auto v:edge[nd]) {
    if (!vis[v]) {
      if(!DFS(v,x^1)) {
	return false;
      }
    } else {
      if (!(odd[v] ^ x)) {
	return false;
      }
    }
  }
  return true;
}

ll mypow (ll base,ll ex) {
  if (ex == 0) {
    return 1;
  } else if (ex == 1) {
    return base;
  } else {
    ll tmp = mypow(base,ex/2);
    tmp = tmp*tmp%MOD;
    return (ex&1)?tmp*base%MOD:tmp;
  }
  
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> t;
    while (t--) {
      cin >> n >> m;
      REP1 (i,n) {
	edge[i].clear();
      }
      REP (i,m) {
	ll u,v;
	cin >> u >> v;
	edge[u].eb(v);
	edge[v].eb(u);
      }

      REP1 (i,n) {
	vis[i] = false;
      }
      //      memset(vis,0,sizeof(bool)*(n+3));

      ll ans = 1;
      bool flag = true;
      REP1 (i,n) {
	if (!vis[i]) {
	  oc = 0;
	  ec = 0;
	  if(!DFS(i,1)) {
	    flag = false;
	  }
	  debug(oc,ec);
	  if (flag) {
	    ans = (mypow(2,oc)+mypow(2,ec))*ans%MOD;
	  } else {
	    ans = 0;
      	  }
	}	
      }

      cout << ans << endl;
    }
    return 0;
}
