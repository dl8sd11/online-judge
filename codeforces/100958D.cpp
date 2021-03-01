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

vector<vector<int> > rmv;
signed main () {
    TIME(main);
    IOS();

    int h, w, n;
    cin >> h >> w >> n;

    rmv.resize(h+1);

    for (int i=0; i<n; i++) {
        int x, y;
        cin >> x >> y;
        rmv[x].eb(y);
    }

    deque<int> odd, even;
    for (int i=1; i<=w; i++) {
        if (i&1) {
            odd.eb(i);
        } else {
            even.eb(i);
        }
    }

    for (int i=1; i<=h; i++) {
        if (i&1) {
            swap(odd, even);
        } else {
            swap(odd,even);
            odd.emplace_front(even.front());
            even.pop_front();
            even.emplace_back(odd.back());
            odd.pop_back();
        }
        for (int x : rmv[i]) {
            debug(x);
            if (x & 1) {
                swap(odd[x/2], even[x/2]);
            } else {
                swap(odd[x/2], even[x/2-1]);
            }
        }
#ifdef tmd
        vector<int> vec;
        for (int j=1; j<=w; j++) {
            if (j&1) {
                vec.eb(odd[j/2]);
            } else {
                vec.eb(even[(j-1)/2]);
            }
        }
        debug(vec);
#endif
    }

    vector<int> ans(w+1);
    for (int j=1; j<=w; j++) {
        if (j&1) {
            ans[odd[j/2]] = j;
        } else {
            ans[even[(j-1)/2]] = j;
        }
    }
    for (int i=1;i<=w; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
