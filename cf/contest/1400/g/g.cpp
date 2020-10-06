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

const ll MOD = 998244353;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 3e5 + 5;
const int MAXM = 41;

int n, m;
vector<pii> rng, edge;

int val[MAXN];
int csum[MAXM][MAXN], fac[MAXN], ifac[MAXN];

int add (int x, int y) {
    x+=y;
    return  x >= MOD ? x - MOD : x;
}

int sub (int x, int y) {
    x-=y;
    return x < 0 ? x + MOD : x;
}

int mul (int x, int y) {
    return ll(x) * y % MOD;
}

int mpow (int bs, int ep) {
    int ret = 1;
    while (ep) {
        if (ep & 1) ret = mul(ret, bs);
        bs = mul(bs, bs);
        ep >>= 1;
    }
    return ret;
}

void build () {
    fac[0] = ifac[0] = 1;
    for (int i=1; i<MAXN; i++) {
        fac[i] = mul(fac[i-1], i);
        ifac[i] = mpow(fac[i], MOD - 2);
    }
}

int cob (int x, int r) {
    return (x < 0 || x < r || r < 0) ? 0 : mul(fac[x], mul(ifac[r], ifac[x-r]));
}

int ans = 0;
bool on[MAXN];
void dfs (int id) {
    if (id == m) {
        set<int> st;

        int L = 1, R = n, cnt = 0;
        for (int i=0; i<m; i++) {
            if (on[i]) {
                cnt++;
                st.insert(edge[i].X);
                st.insert(edge[i].Y);

                L = max(L, rng[edge[i].X].X);
                L = max(L, rng[edge[i].Y].X);

                R = min(R, rng[edge[i].X].Y);
                R = min(R, rng[edge[i].Y].Y);
            }
        }

        if (L <= R) {
            int cur = sub(csum[SZ(st)][R], csum[SZ(st)][L-1]);
            pary(on, on+m);
            debug(L, R, cur);
            ans = add(ans, mul(cur, ((cnt & 1) ? MOD-1 : 1)));
        }
    } else {
        dfs(id+1);
        on[id] = true;
        dfs(id+1);
        on[id] = false;
    }
}
signed main () {
    TIME(main);
    IOS();
    build();

    cin >> n >> m;
    rng.resize(n);
    for (int i=0; i<n; i++) {
        cin >> rng[i].X >> rng[i].Y;
    }

    edge.resize(m);
    for (int i=0; i<m; i++) {
        cin >> edge[i].X >> edge[i].Y;
        edge[i].X--;
        edge[i].Y--;
    }

    for (int i=0; i<n; i++) {
        val[rng[i].X]++;
        val[rng[i].Y+1]--;
    }
    for (int i=1; i<=n; i++) {
        val[i] += val[i-1];
    }
    pary(val, val+n+1);

    for (int i=0; i<MAXM; i++) {
        for (int j=1; j<=n; j++) {
            csum[i][j] = cob(val[j]-i, j-i);
            csum[i][j] = add(csum[i][j], csum[i][j-1]);
        }
    }
    pary(csum[0], csum[0]+n+1);
    pary(csum[1], csum[1]+n+1);
    pary(csum[2], csum[2]+n+1);

    dfs(0);
    cout << ans << endl;
    return 0;
}
