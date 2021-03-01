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

const int maxn = 51;
struct MaxClique {
    // change to bitset for n > 64.
    int n, deg[maxn];
    uint64_t adj[maxn], ans;
    vector<pair<int, int>> edge;
    void init(int n_) {
        n = n_;
        fill(adj, adj + n, 0ull);
        fill(deg, deg + n, 0);
        edge.clear();
    }
    void add_edge(int u, int v) {
        edge.emplace_back(u, v);
        ++deg[u], ++deg[v];
    }
    vector<int> operator()() {
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int u, int v) { return deg[u] < deg[v]; });
        vector<int> id(n);
        for (int i = 0; i < n; ++i) id[ord[i]] = i;
        for (auto e : edge) {
            int u = id[e.first], v = id[e.second];
            adj[u] |= (1ull << v);
            adj[v] |= (1ull << u);
        }
        uint64_t r = 0, p = (1ull << n) - 1;
        ans = 0;
        dfs(r, p);
        vector<int> res;
        for (int i = 0; i < n; ++i) {
            if (ans >> i & 1) res.push_back(ord[i]);
        }
        return res;
    }
#define pcount __builtin_popcountll
    void dfs(uint64_t r, uint64_t p) {
        if (p == 0) {
            if (pcount(r) > pcount(ans)) ans = r;
            return;
        }
        if (pcount(r | p) <= pcount(ans)) return;
        int x = __builtin_ctzll(p & -p);
        uint64_t c = p & ~adj[x];
        while (c > 0) {
            // bitset._Find_first(); bitset._Find_next();
            x = __builtin_ctzll(c & -c);
            r |= (1ull << x);
            dfs(r, p & adj[x]);
            r &= ~(1ull << x);
            p &= ~(1ull << x);
            c ^= (1ull << x);
        }
    }
};


signed main () {
    TIME(main);
    IOS();

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        MaxClique cl;
        cl.init(n);

        vector<int> a(n);
        for (int i=0; i<n; i++) {
            cin >> a[i];
        }

        for (int i=0; i<n; i++) {
            for (int j=0; j<i; j++) {
                if (__builtin_popcount(a[i] ^ a[j]) != 1) {
                    cl.add_edge(i, j);
                }
            }
        }

        vector<int> ans = cl();

        cout << SZ(ans) << endl;
        vector<int> rans;
        for (auto v : ans) rans.eb(a[v]);

        for (int i=0; i<SZ(ans); i++) {
            cout << rans[i] << " \n"[i==SZ(ans)-1];
        }
    }

    return 0;
}
