#pragma GCC optimize("Ofast", "unroll-loops")
#pragma GCC target("avx", "avx2", "fma")
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
const ll MAXN = 3e5 + 5;

int N;
int bit[MAXN];
void add (int x, int v) {
    for (x++; x<N; x+=-x&x) {
        bit[x] += v;
    }
}

int qry (int x) {
    int ret = 0;
    for (x++; x; x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

int n;
int a[MAXN], v[MAXN];
ll inv () {
    int sz;
    ll sum = 0;
    {
        TIME(s1);

        for (int i=0; i<n; i++) {
            v[i]  = a[i];
        }
        sort(v, v+n);
        sz = unique(v,v+n) - v;
        N = sz + 3;
    }
    {

        TIME(s2);
        for (int i=0; i<n; i++) {
            int r = lower_bound(v,v+sz, a[i])-v;
            sum += qry(r);
            add(r, 1);
        }
    }
    return n * (n - 1LL) / 2 - sum;
}
signed main () {
    TIME(main);
    IOS();

    cin >> n;
    for (int i=0; i<n; i++) {
#ifdef tmd
        a[i] = rand();
#else
        cin >> a[i];
#endif
    }

    int x = 0;
    vector<int> id(n);
    iota(ALL(id), 0);
    for (int i=30; i>=0; i--) {
        {
            TIME(b1);
            sort(ALL(id), [&](int l, int r) {
                int x = (a[l]>>(i+1)) - (a[r]>>(i+1));
                return x == 0 ? l < r : x < 0;
            });
        }

        ll c01 = 0, c10 = 0;
        ll c0 = 0, c1 = 0;
        {
            TIME(b2);
            for (int j=0; j<n; j++) {
                if ((a[id[j]]>>i)&1) {
                    c01 += c0;
                    c1 += 1;
                } else {
                    c10 += c1;
                    c0 += 1;
                }
                if (j == (n-1) || (a[id[j]]>>(i+1) < a[id[j+1]]>>(i+1)) ) {
                    c0 = c1 = 0;
                }
            }

            if (c01 < c10) {
                x ^= 1<<i;
                for (int j=0; j<n; j++) a[j] ^= (1<<i);
            }
        }
    }


    cout << inv() << " " << x << endl;

    return 0;
}

