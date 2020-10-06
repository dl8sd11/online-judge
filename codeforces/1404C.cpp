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

vector<int> a, f, v, pre;


struct Bit {
    int N;
    vector<int> bit;
    Bit (int n) : N(n+5), bit(n+5) {
    }

    void add (int x, int val) {
        for (x+=2; x<N; x+=-x&x) {
            bit[x] += val;
        }
    }

    int qry (int x) {
        int res = 0;
        for (x+=2; x; x-=-x&x) {
            res += bit[x];
        }
        return res;
    }
};

signed main () {
    TIME(main);
    IOS();

    int n, q;
    cin >> n >> q;
    n++;
    a.resize(n);
    f.resize(n);
    v.resize(n);
    pre.resize(n);
    Bit tme(n);

    a[0] = MOD;
    for (int i=0; i<n; i++) {
        if (i) cin >> a[i];
    }

    vector<int> ans(q);
    vector<pii> qry(q);
    vector<vector<int> > add(n), sub(n);
    for (int i=0; i<q; i++) {
        cin >> qry[i].X >> qry[i].Y;
        add[n-1-qry[i].Y].eb(i);
        sub[qry[i].X].eb(i);
    }

    for (int i=0; i<n; i++) {
        v[i] = i - a[i];
        if (v[i] < 0) v[i] = MOD;

        int L=-1, R=i;
        while (L < R - 1) {
            int M = (L + R) >> 1;
            if (v[i] - tme.qry(M) <= 0) {
                L = M;
            } else {
                R = M;
            }
        }
        tme.add(0, 1);
        tme.add(R, -1);
        debug(i, R);

        for (int id : add[i]) {
            ans[id] += tme.qry(qry[id].X);
        }
        //for (int id : sub[i]) {
            //ans[id] -= tme.qry(qry[id].X);
        //}
    }
    debug(v);


    for (int i=0; i<q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}

