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
const ll MAXN = 202 * 202 * 2;

int n, m, S, T;

int gv (int r, int c) {
    return m*r + c;

}

int gh (int r, int c) {
    return m*(n+1) + r*(m+1) + c;
}

struct Edge {
    int t, flow, cap, nxt;
} edge[MAXN*20];
int head[MAXN], lev[MAXN], ecnt, cur[MAXN];

void add_edge (int u, int v, int cap) {
    edge[ecnt++] = Edge({v, 0, cap, head[u]});
    head[u] = ecnt-1;
    edge[ecnt++] = Edge({u, 0, 0, head[v]});
    head[v] = ecnt-1;
}

bool bfs () {
    MEM(lev, -1);
    lev[S] = 0;
    queue<int> que;
    que.emplace(S);
    while (que.size()) {
        int x = que.front();
        que.pop();
        for (int it=head[x]; it!=-1; it=edge[it].nxt) {
            int y = edge[it].t;
            if (edge[it].flow < edge[it].cap && lev[y] == -1) {
                lev[y] = lev[x] + 1;
                que.emplace(y);
            }
        }
    }

    return lev[T] != -1;
}

int dfs (int nd, int lim) {
    if (nd == T || lim == 0) {
        return lim;
    }
    for (int &it=cur[nd]; it!=-1; it=edge[it].nxt) {
        int y = edge[it].t;
        int rem = edge[it].cap - edge[it].flow;
        if (lev[y] == lev[nd] + 1 && rem > 0) {
            int df = dfs(y, min(lim, rem));
            if (df) {
                edge[it].flow += df;
                edge[it^1].flow -= df;
                return df;
            }

        }
    }
    return 0;
}

int mf () {
    int flow = 0;
    while (bfs()) {
        int df = 0;
        for (int i=0; i<=T; i++) {
            cur[i] = head[i];
        }

        while (df = dfs(S, MOD)) {
            flow += df;
        }
    }
    return flow;

}
signed main () {
    TIME(main);
    IOS();
    cin >> n >> m;
    vector<vector<int> > g(n, vector<int>(m));
    MEM(head, -1);

    int sum = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            char c;
#ifdef tmd
            c = '#';
#else
            cin >> c;
#endif
            g[i][j] = c == '#';
            sum += g[i][j];
        }
    }

    S = m*(n+1) + (m+1)*n;
    T = m*(n+1) + (m+1)*n + 1;

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            add_edge(gv(i, j), gh(i,j), 1);
            add_edge(gv(i, j), gh(i,j+1), 1);
            add_edge(gv(i+1, j), gh(i,j), 1);
            add_edge(gv(i+1, j), gh(i,j+1), 1);
        }
    }

    int vs = 0;
    for (int i=1; i<n; i++) {
        for (int j=0; j<m; j++) {
            if (g[i][j] && g[i-1][j]) {
                vs++;
                add_edge(S, gv(i, j), 1);
            }
        }
    }

    for (int j=1; j<m; j++) {
        for (int i=0; i<n; i++) {
            if (g[i][j] && g[i][j-1]) {
                add_edge(gh(i, j), T, 1);
                vs++;
            }
        }
    }

    int f = mf();
    debug(sum, f, vs);
    cout << sum - (vs-f) << endl;
    return 0;
}

