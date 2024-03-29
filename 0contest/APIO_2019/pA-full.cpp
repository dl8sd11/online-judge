#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#ifdef tmd
typedef __int128 lll;
#else
typedef __int128 lll;
#endif
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
template<typename _a> ostream &operator << (ostream &_s, const array<_a,2> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const array<_a,3> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const array<_a,4> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const array<_a,5> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const set<_a> &_c) {return _OUTC(_s, ALL(_c));}
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

void extGCD(lll A,lll B,lll &x,lll &y) { // A p coprime
    if (B == 0) {
        x = 1;
        y = 0;
        assert(A == 1);
        return;
    }
    lll xx,yy;
    extGCD(B,A%B,xx,yy);
    x = yy;
    y = xx - A/B*yy;
    return;
}

lll ext_inv (lll a, lll p) { // a, p co-prime
    lll x, y;
    extGCD(a,p, x, y);
    x %= p;
    if (x < 0) {
        x += p;
    }
    assert(a * x % p);
    return x;
}

lll di (lll a, lll b, lll md) {
    if (a == 0) {
        return 0;
    }
    assert(b != 0);
    lll cd = __gcd( __gcd(a, b), md);
    a /= cd;
    b /= cd;
    md /= cd;
    
    return ext_inv(b,md) * a % md;
}
signed main () {
    TIME(main);
    IOS();


    ll n, a, b;
    cin >> n >> a >> b;

    lll sz = b*lll(a/__gcd(a,b+1));
    vector<pair<lll,lll>> seg;
    lll g = (b+1) % a;

    lll LS = 0;
    bool gg= false;
    for (int i=0; i<n; i++) {
        ll l, r;
        cin >> l >> r;
        if (r-l+1 >= sz) {
            cout << ll(sz) << endl;
            gg = true;
            break;
        } else {
            lll sft = (a+l%a+(l/b)%a-l%b%a)%a;
            lll rw = di(sft, g, a);
            lll st = l%b + b*rw;
            lll ed = st + r-l;
            st %= sz;
            ed %= sz;
            if (ed < st) {
                seg.eb(0, ed);
                seg.eb(st, sz-1);
            } else {
                seg.eb(st, ed);
            }

        }
    }
    if (gg) {
        return 0;
    }
    sort(ALL(seg));

    lll lst = -1;
    lll ans = 0;
    for (auto p : seg) {
        ans += max(lll(0), p.Y - max(lst+1, p.X) + 1);
        lst = max(lst, p.Y);
    }

    cout << ll(ans) << endl;


    return 0;
}
