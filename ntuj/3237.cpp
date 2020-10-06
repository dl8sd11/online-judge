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
// Cipolla algo from https://oi-wiki.org/math/quad-residue/
ll w;
struct num {

  ll x, y;
};

num mul(num a, num b, ll p) {
  num ans = {0, 0};
  ans.x = ((a.x * b.x % p + a.y * b.y % p * w % p) % p + p) % p;
  ans.y = ((a.x * b.y % p + a.y * b.x % p) % p + p) % p;
  return ans;
}

ll binpow_real(ll a, ll b, ll p) {
  ll ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % p;
    a = a * a % p;
    b >>= 1;
  }
  return ans % p;
}

ll binpow_imag(num a, ll b, ll p) {
  num ans = {1, 0};
  while (b) {
    if (b & 1) ans = mul(ans, a, p);
    a = mul(a, a, p);
    b >>= 1;
  }
  return ans.x % p;
}

ll cipolla(ll n, ll p) {
  n %= p;
  if (n == 0) return 0;
  if (p == 2) return n;
  if (binpow_real(n, (p - 1) / 2, p) == p - 1) return -1;
  ll a;
  while (1) {
    a = rand() % p;
    w = ((a * a % p - n) % p + p) % p;
    if (binpow_real(w, (p - 1) / 2, p) == p - 1) break;
  }
  num x = {a, 1};
  return binpow_imag(x, (p + 1) / 2, p);
}

ll nm (ll x, ll p) {
    return ((x % p) + p) % p;
}

signed main () {
    TIME(main);
    IOS();

    int n;
    cin >> n;
    while (n--) {
        ll p, a0, a1;
#ifdef tmd
        p = 880301;
        a0 = rand() % 880300 + 1;
        a1 = rand() % 880300 + 1;
#else
        cin >> p >> a0 >> a1;
#endif
        if (p == 2) {
            if (a0 + a1 == 0) {
                cout << "0 0" << endl;
            } else if (a0 + a1 == 1) {
                if (a0 == 1) {
                    cout << "1 1" << endl;
                } else {
                    cout << "0 1" << endl;
                }
            } else {
                cout << -1 << endl;
            }
            continue;
        }
        ll sq2 = nm(a1*a1-4*a0, p) % p;
        debug(sq2);
        ll sq = cipolla(sq2, p);
        debug(sq2, sq);
        if (sq == -1) {
            cout << -1 << endl;
        } else {
            ll hf = binpow_real(2, p-2, p);
            ll b0 = (a1 + sq) * hf % p;
            ll b1 = nm(a1 - sq,p) * hf % p;
            if (b0 > b1) swap(b0, b1);
            cout << b0 << " " << b1 << endl;
#ifdef tmd
            assert(b0 * b1 % p == a0);
            assert((b0 + b1) % p == a1);
#endif
        }
    }

    return 0;
}

