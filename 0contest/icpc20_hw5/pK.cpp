#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double, double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) static_cast<int>(i.size())
#define FOR(i, j, k, in) for (int i=j; i < (k) ; i+=in)
#define RFOR(i, j, k, in) for (int i=j; i >= (k) ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i, j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(), _a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
template<typename T, typename S>
istream &operator >> (istream &is, pair<T, S> &p) {
    return is >> p.X >> p.Y;
}
#ifdef tmd
#define TIME(i) Timer i(#i)
#define debug(...) do {\
    fprintf(stderr, "%s - %d (%s) = ", __PRETTY_FUNCTION__, __LINE__, #__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T> void _do(T &&_x) {cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x, S &&..._t) {cerr <<_x <<" ,"; _do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s, const pair<_a, _b> &_p) {return _s << "(" << _p.X << "," << _p.Y << ")";}
template<typename It> ostream& _OUTC(ostream &_s, It _ita, It _itb)
{
    _s << "{";
    for (It _it=_ita; _it != _itb; _it++) {
        _s <<(_it == _ita?"":",")<< *_it;
    }
    _s << "}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s, const vector<_a> &_c) {return _OUTC(_s,ALL(_c));}
template<typename _a, size_t _b> ostream &operator << (ostream &_s, const array<_a,_b> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const deque<_a> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s, const map<_a,_b> &_c) {return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
class Timer {
private:
    string scope_name;
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer (string name) : scope_name(name) {
        start_time = chrono::high_resolution_clock::now();
    }
    ~Timer () {
        auto stop_time = chrono::high_resolution_clock::now();
        auto length = chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
        double mlength = double(length) * 0.001;
        debug(scope_name, mlength);
    }
};
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 2e5 + 5;

ll fmul (ll a, ll b, ll m) {
    ll res = 0;
    assert(m < INF);
    a %= m;
    while (b) {
        if (b&1) res = (((res + a) >= m) ? (res + a - m) : (res + a));
        a = ((a + a >= m) ? (a + a - m) : (a + a));
        b >>= 1;
    }
    return res;
}

ll fpow (ll b, ll e, ll m) {
    ll res = 1;
    while (e) {
        if (e&1) res = fmul(res, b, m);
        b = fmul(b, b, m);
        e>>=1; 
    }
    return res;
}
vector<long long> chk = {2,325,9375,28178,450775,9780504,1795265022};
bool Check(long long a, long long u, long long n, int t) {
    a = fpow(a, u, n);
    if (a == 0 || a == 1 || a == n - 1) return true;
    for (int i = 0; i < t; ++i) {
        a = fmul(a, a, n);
        if (a == 1) return false;
        if (a == n - 1) return true;
    }
    return false;
}
bool IsPrime(long long n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    long long u = n - 1; int t = 0;
    for (; !(u & 1); u >>= 1, ++t);
    for (long long i : chk) {
        if (!Check(i, u, n, t)) return false;
    }
    return true;
}

bool test (ll nd) {
    if (nd %  2 == 0) return false;
    if (nd == 9) return true;
    return IsPrime(nd);
}

signed main () {
    TIME(main);
    IOS();


    ll a, b;
    while (cin >> a >> b) {
        vector<ll> v;
        for (ll i=a; i<=b; i++) {
            if (test(i)) {
                v.eb(i);
            }
        }
        for (int i=0; i<SZ(v); i++) {
            cout << v[i] << " \n"[i==SZ(v)-1];
        }
    }


    return 0;
}
