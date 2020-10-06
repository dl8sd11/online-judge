#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
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

vector<int> lside (const vector<int> &l, const vector<int> &h, int w) {

    set<pii> cover;

    ll cs = h[0]%MOD, ct = w;
    ll n = SZ(l);
    cover.insert({0, -1});
    cover.insert({h[0], 0});
    vector<int> ps = {int((cs + ct)%MOD)};

    for (int i=1, ptr=0; i<n; i++) {
        while (ptr < n && l[i] - l[ptr] > w) {
            cover.erase({h[ptr], ptr});
            ptr++;
        }

        cs = (cs + max(0LL, h[i]-(prev(cover.end())->X))) % MOD;
        cover.insert({h[i], i});

        ct = (ct + min(l[i]-l[i-1], w)) % MOD;

        int p = (cs + ct) % MOD;
        ps.eb(p);
    }
    return ps;
}

vector<int> rside (const vector<int> &l, const vector<int> &h, int w) {


    ll cs = h[0], ct = w;
    ll n = SZ(l);
    deque<int> deq = { 0 };
    vector<int> ps = {int((cs + ct)%MOD)};

    for (int i=1, ptr=0; i<n; i++) {
        while (deq.size() && l[i] - l[deq.front()] > w) {
            deq.pop_front();
        }

        int mx = 0;
        while (deq.size() && h[deq.back()] < h[i]) {
            mx = max(mx, h[deq.back()]);
            deq.pop_back();
        }

        if (deq.empty()) {
            cs = (cs + h[i] - mx) % MOD;
        }
        ct = (ct + min(l[i]-l[i-1], w)) % MOD;
        deq.push_back(i);

        int p = (cs + ct) % MOD;
        ps.eb(p);
    }
    return ps;
}

vector<int> add (const vector<int> &v1, const vector<int> &v2) {
    vector<int> res(SZ(v1));
    for (int i=0; i<SZ(v1); i++) {
        res[i] = (v1[i] + v2[i]) % MOD;
    }
    return res;
}

int pro (const vector<int> &p) {
    int res = 1;
    for (auto v : p) {
        res = (1LL * res * v) % MOD;
    }
    return res;
}

int calc (const vector<int> &l, const vector<int> &h, int w) {
    debug(l);
    debug(h);

    vector<int> lres = lside(l, h, w);
    vector<int> rres = rside(l, h, w);
    vector<int> sum = add(lres, rres);
    debug(lres);
    debug(rres);
    debug(sum);

    return pro(sum); 
}

void solve (int tid) {
    int n, k, w;
    cin >> n >> k >> w; 
    vector<vector<int> > dt;
    for (int i=0; i<2; i++) {
        vector<int> cur(n);
        for (int j=0; j<k; j++) {
                cin >> cur[j];
        }
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        for (int j=k; j<n; j++) {
            cur[j] = (cur[j-2]*a + cur[j-1]*b + c) % d + 1;
        }
        dt.eb(cur);
    }
    int res = calc(dt[0], dt[1], w);
    cout << "Case #" << tid << ": " << res  << endl;
}
signed main () {
    TIME(main);
    IOS();

    int ts;
    cin >> ts;
    for (int i=1; i<=ts; i++) {
        solve(i);
    }
    return 0;
}
