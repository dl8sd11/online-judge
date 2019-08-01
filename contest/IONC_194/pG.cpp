#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
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
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 100005;


template<typename F = long long>
struct Linear { // y = a * x + b;
  F a, b;
  Linear(F a = 0, F b = 0) : a(a), b(b) {}
  bool operator<(Linear oth) const {
    return a == oth.a ? b < oth.b : a < oth.a;
  }
  template<typename T> T operator()(T x) const { return a * x + b; }
};


template<typename F = long long>
class ConvexHull { // lower envelop
  vector<Linear<F>> f;
  bool cross(Linear<F> P, Linear<F> Q, Linear<F> T) const {
    if (Q.a == T.a) return Q.b <= T.b;
    auto ceil2 = [=](F a, F b) {
      return a >= 0 ? (a + b - 1) / b : a / b;
    };
    const F x = ceil2(P.b - Q.b, Q.a - P.a);
    const F y = ceil2(Q.b - T.b, T.a - Q.a);
    return y <= x;
  }
  void getHull() {
    int m = 0;
    for (int i = 0; i < f.size(); ++i) {
      while (m >= 2 and cross(f[m - 2], f[m - 1], f[i]))  --m;
      if (m == 1 and f[0].a == f[i].a) --m;
      f[m++] = f[i];
    }
    f.resize(m);
  }
public:
  int size() const { return f.size(); }
  ConvexHull(vector<Linear<F>> A) : f(A) {
    sort(f.begin(), f.end());
    getHull();
  }
  F operator()(F x) const {
    int n = f.size();
    auto df = [&](int i) { return f[i + 1](x) - f[i](x); };
    if (n == 0) return numeric_limits<F>::min();
    if (n == 1 or df(0) <= 0) return f[0](x);
    int l = 0, r = n - 1;
    while (r - l > 1) {
      int m = l + r >> 1;
      (df(m) < 0 ? r : l) = m;
    }
    return max({f[r](x),f.front()(x), f.back()(x)});
  }

  void merge(const ConvexHull &oth) {
    auto mid = f.size();
    f.insert(f.end(), oth.f.begin(), oth.f.end());
    inplace_merge(f.begin(), f.begin() + mid, f.end());
    getHull();
  }

};


template<typename F>
class ExpandableHull {
  vector<ConvexHull<F>> stk;
public:
  void addLine(Linear<F> l) {
    stk.emplace_back(vector<Linear<F>>{l});
    int m = stk.size();
    while (m > 1 and stk[m - 2].size() <= stk[m - 1].size()) {
      stk[m - 2].merge(stk[m - 1]);
      stk.pop_back();
      --m;
    }
  }
  F operator()(F x) {
    return accumulate(stk.begin(), stk.end(), numeric_limits<F>::min(),
      [&](F y, ConvexHull<F>& C) { return max(y, C(x)); 
    });
  }
};


ll n, a[MAXN], b[MAXN], dp[MAXN];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;

    REP (i, n) {
        cin >> a[i] >> b[i];
    }

    ExpandableHull<ll> hull;
    dp[0] = 0;
    REP1 (i, n) {
        hull.addLine(Linear<ll>(b[i-1],dp[i-1]));
        dp[i] = hull(a[i-1]);
    }

    cout << dp[n] << endl;
    return 0;
}
