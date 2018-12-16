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

const ll MOD=1000000007;
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAXN=1e5+5;
const ll MAXLG=__lg(MAXN)+2;

ll n,ans[MAXN];
struct POINT {
  ll x,y,z,pid;
}pt[MAXN];

bool cmpX (const POINT &a,const POINT &b) {
  return a.x > b.x;
}

ll bit[MAXN];
void add(ll pos,ll val) {
  for (;pos<MAXN;pos+=-pos&pos) {
    bit[pos] += val;
  }
}

ll sum(ll pos) {
  ll ret = 0;
  for (;pos>=1;pos-=-pos&pos) {
    ret += bit[pos];
  }
  return ret;
}

ll bit2[MAXN];
void add2(ll pos,ll val) {
  for (;pos<MAXN;pos+=-pos&pos) {
    bit2[pos] += val;
  }
}

ll sum2(ll pos) {
  ll ret = 0;
  for (;pos>=1;pos-=-pos&pos) {
    ret += bit2[pos];
  }
  return ret;
}


void solve(ll L,ll R) {
  if (L == R - 1) {
    return;
  }
  ll mid = L+R>>1;
  solve(L,mid);
  solve(mid,R);

  vector<pii> sq;
  for (ll i=L;i<mid;i++) sq.eb(i,0);
  for (ll i=mid;i<R;i++) sq.eb(i,1);
  sort(ALL(sq),[](const pii &a,const pii &b){return pii(pt[a.X].y,a.Y) > pii(pt[b.X].y,b.Y);});
  ll ov = -INF;
  if (pt[mid-1].x == pt[mid].x) ov = pt[mid-1].x;

  for (auto p:sq) {
    if (p.Y == 1) {
      ans[pt[p.X].pid] += sum(MAXN-1) - sum(pt[p.X].z);
      if (pt[p.X].x == ov) {
        ans[pt[p.X].pid] -= (sum2(MAXN-1) - sum2(pt[p.X].z));
      }
    } else {
      add(pt[p.X].z,1);
      if (pt[p.X].x == ov) add2(pt[p.X].z,1);
    }
  }

  for (ll i=L;i<mid;i++) {
    add(pt[i].z,-1);
    if (pt[i].x == ov) add2(pt[i].z,-1);
  }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n) {
      ll x,y,z;
      cin >> x >> y >> z;
      pt[i] = (POINT){x,y,z,i};
    }

    sort(pt,pt+n,cmpX);

    REP (i,n) {
      debug(pt[i].pid);
    }
  
    solve(0,n);

    REP (i,n) {
      cout << ans[i] << endl;
    }

    return 0;
}
