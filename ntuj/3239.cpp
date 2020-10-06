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
const ll MAXN = 1e5 + 5;

struct Data {
    ll pre, suf, sum, mx;
};
Data mrg (const Data &d1, const Data &d2) {
    Data res;
    res.pre = max(d1.sum + d2.pre, d1.pre);
    res.suf = max(d1.suf + d2.sum, d2.suf);
    res.sum = d1.sum + d2.sum;
    res.mx = max({d1.mx, d2.mx, d1.suf + d2.pre});
    return res;
}

Data seg[MAXN*2];

ll n;
void build () {
    for (ll i=n-1; i>0; i--) {
        seg[i] = mrg(seg[i<<1], seg[i<<1|1]);
    }
}

void chg (ll x, ll y) {
    x+=n;
    seg[x] = {max(y,0LL), max(y,0LL), y, max(y,0LL)};
    for (;x>1; x>>=1) {
        ll l = min(x,x^1);
        ll r = max(x, x^1);
        seg[x>>1] = mrg(seg[l], seg[r]);
    }
}

ll qry (ll l, ll r) {
    vector<ll> L, R;
    for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
        if (l&1) L.eb(l++);
        if (r&1) R.eb(--r);
    }
    Data res = {0, 0, 0, 0};
    for (ll id : L) res = mrg(res, seg[id]);
    reverse(ALL(R));
    for (ll id : R) res = mrg(res, seg[id]);
    return res.mx;
}

ll a[MAXN];

void st (ll id) {
    if (id == 0 || id == n-1) chg(id, -MOD);
    else {
        if (a[id] < a[id-1] && a[id] < a[id+1]) chg(id, -MOD);
        else chg(id, 1);
    }
}
signed main () {
    TIME(main);
    IOS();

    ll t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (ll i=0; i<n; i++) cin >> a[i];
        for (int i=0; i<n*2; i++) {
            seg[i] = {0, 0, 0, 0};
        }
        for (ll i=0; i<n; i++) {
            st(i);            
        }

        ll q;
        cin >> q;
        while (q--) {
            ll c, l, r;
            cin >> c >> l >> r;
            if (c == 1) {
                a[l] += r;
                st(l);
                if (l) st(l-1);
                if (l+1<n) st(l+1);
            } else {
                if (l > r) swap(l, r);
                chg(l, -MOD);
                chg(r, -MOD);
                cout << min(r-l+1, qry(l, r+1)+2) << endl;
                st(l);
                st(r);
            }
        }
    }

    return 0;
}

