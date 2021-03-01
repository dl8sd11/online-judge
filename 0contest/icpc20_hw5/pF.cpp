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

const int inf = 0x3f3f3f3f;
const int maxn = 601;

template <typename T> struct DMST {
    T g[maxn][maxn], fw[maxn];
    int n, fr[maxn];
    bool vis[maxn], inc[maxn];
    void clear() {
        for(int i = 0; i < maxn; ++i) {
            for(int j = 0; j < maxn; ++j) g[i][j] = inf;
            vis[i] = inc[i] = false;
        }
    }
    void addedge(int u, int v, T w) {
        debug(u, v, w);
        u++, v++;
        g[u][v] = min(g[u][v], w);
    }
    T operator()(int root, int _n) {
        root++;
        n = _n;
        if (dfs(root) != n) return -1;
        T ans = 0;
        while (true) {
            for (int i = 1; i <= n; ++i) fw[i] = inf, fr[i] = i;
            for (int i = 1; i <= n; ++i) if (!inc[i]) {
                for (int j = 1; j <= n; ++j) {
                    if (!inc[j] && i != j && g[j][i] < fw[i]) {
                        fw[i] = g[j][i];
                        fr[i] = j;
                    }
                }
            }
            int x = -1;
            for (int i = 1; i <= n; ++i) if (i != root && !inc[i]) {
                int j = i, c = 0;
                while (j != root && fr[j] != i && c <= n) ++c, j = fr[j];
                if (j == root || c > n) continue;
                else { x = i; break; }
            }
            if (!~x) {
                for (int i = 1; i <= n; ++i) if (i != root && !inc[i]) ans += fw[i];
                return ans;
            }
            int y = x;
            for (int i = 1; i <= n; ++i) vis[i] = false;
            do { ans += fw[y]; y = fr[y]; vis[y] = inc[y] = true; } while (y != x);
            inc[x] = false;
            for (int k = 1; k <= n; ++k) if (vis[k]) {
                for (int j = 1; j <= n; ++j) if (!vis[j]) {
                    if (g[x][j] > g[k][j]) g[x][j] = g[k][j];
                    if (g[j][k] < inf && g[j][k] - fw[k] < g[j][x]) g[j][x] = g[j][k] - fw[k];
                }
            }
        }
        return ans;
    }
    int dfs(int now) {
        int r = 1;
        vis[now] = true;
        for (int i = 1; i <= n; ++i) if (g[now][i] < inf && !vis[i]) r += dfs(i);
        return r;
    }
};

DMST<int> dmst;
signed main () {
    TIME(main);
    IOS();

    int n, m;
    while (cin >> n >> m && n) {
        vector<int> a(n);

        int sum = 0;
        vector<vector<int> > lid(n);

        dmst.clear();
        for (int i=0; i<n; i++) {
            cin >> a[i];
            for (int j=0; j<=a[i]; j++) {
                if (j) dmst.addedge(sum, lid[i].back(), 0);
                lid[i].eb(sum++);
            }
        }

        for (int i=0; i<n; i++) {
            dmst.addedge(sum, lid[i].front(), 0);
        }
        sum++;

        for (int i=0; i<m; i++) {
            int fi, fj, ti, tj, cost;
            cin >> fi >> fj >> ti >> tj >> cost;
            dmst.addedge(lid[fi-1][fj], lid[ti-1][tj], cost);
        }

        cout << dmst(sum-1, sum) << endl;
    }


    return 0;
}
