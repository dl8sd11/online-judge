#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
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
}while(0);
template<typename T> void _do(T &&_x) {cerr<<_x<<endl;}
template<typename T, typename ...S> void _do(T &&_x, S &&..._t) {cerr <<_x <<", "; _do(_t...);}
template<typename _a, typename _b> ostream& operator << (ostream &_s, const pair<_a, _b> &_p) {return _s << "(" << _p.X << ", " << _p.Y << ")";}
template<typename It> ostream& _OUTC(ostream &_s, It _ita, It _itb)
{
    _s << "{";
    for (It _it=_ita; _it != _itb; _it++) {
        _s <<(_it == _ita?"":", ")<< *_it;
    }
    _s << "}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s, const vector<_a> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const tree<_a,null_type, less<_a>, rb_tree_tag, tree_order_statistics_node_update> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a, size_t _b> ostream &operator << (ostream &_s, const array<_a, _b> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s, const deque<_a> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _a, typename _b> ostream &operator << (ostream &_s, const map<_a, _b> &_c) {return _OUTC(_s, ALL(_c));}
template<typename _t> void pary(_t _a, _t _b){_OUTC(cerr, _a, _b);cerr<<endl;}
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

const int MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const int MAXN = 1e5 + 5;
const int MAXLG = __lg(MAXN) + 3;

tree<pli, null_type, less<pli>, rb_tree_tag, tree_order_statistics_node_update> tp[MAXN], tc[MAXN];
int n, q;
vector<pii> edge[MAXN];
bool dead[MAXN];
int sz[MAXN], dep[MAXN], pG[MAXN];
ll anc[MAXN][MAXLG], ranc[MAXN][MAXLG];

int OneCentroid(int rt) {
    function<void (int, int)> get_sz = [&](int nd, int par) {
        sz[nd] = 1;
        for (auto [v, w] : edge[nd]) {
            if (v != par && !dead[v]) {
                get_sz(v, nd);
                sz[nd] += sz[v];
            }
        }
    };
    get_sz(rt, -1);
    int hf = sz[rt] / 2;
    function<int (int, int)> dfs = [&](int nd, int par) {
        for (auto [v, w] : edge[nd]) {
            if (v != par && !dead[v] && sz[v] > hf) {
                return dfs(v, nd);
            }
        }
        return nd;
    };
    return dfs(rt, rt);
}

void CentroidDecomposition() {

    function<void (int, int, ll, int, int)> get_child = [&](int nd, int par, ll d, int lev, int root) {
        anc[nd][lev] = d;
        ranc[nd][lev] = root;
        for (auto [v, w] : edge[nd]) {
            if (v != par && !dead[v]) {
                get_child(v, nd, d+w, lev, root);
            }
        }
    };
    function<void (int, int, int)> rec = [&](int start, int par, int lev) {
        int c = OneCentroid(start);
        dead[c] = true;
        pG[c] = par;
        dep[c] = lev;

        get_child(c, -1, 0, lev, c);

        for (auto [v, w] : edge[c]) {
            if (!dead[v]) {
                rec(v, c, lev+1);
            }
        }

        dead[c] = false;
    };
    rec(1, -1, 0);
}


void chg(int start, bool add) {
    function<void (int)> pull = [&](int nd) {
        ll dis = anc[start][dep[nd]];
        if (add) {
            tp[nd].insert({dis, start});
            if (nd != start) {
                tc[ranc[start][dep[nd]+1]].insert({dis, start});
            }

        } else {
            tp[nd].erase({dis, start});
            if (nd != start) {
                tc[ranc[start][dep[nd]+1]].erase({dis, start});
            }
        }
        if (pG[nd] != -1) {
            pull(pG[nd]);
        }
    };
    pull(start);
}

int qry(int start, ll lim) {
    int ret = 0;
    function<void (int)> pull = [&](int nd) {
        ll dis = lim - anc[start][dep[nd]];
        if (dis >= 0) {
            int ord = tp[nd].order_of_key({dis, MOD});
            ret += ord;
            debug(nd, dis, ord);
        }
        if (pG[nd] != -1) {
            ll d2 = lim - anc[start][dep[nd]-1];
            if (d2 >= 0) {
                int ord = tc[nd].order_of_key({d2, MOD});
                ret -= ord;
                debug(nd, d2, ord);
            }
            pull(pG[nd]);
        }
    };
    pull(start);
    return ret;
}

ll kth (int nd, int k) {
    ll L = -1, R = 1e14 + 14;
    while (L < R - 1) {
        ll M = (L + R) >> 1;
        int res = qry(nd, M);
        debug(nd, M, res);
        if (res >= k) {
            R = M;
        } else {
            L = M;
        }
    }
    return R;
}
signed main () {
    TIME(main);
    IOS();
    cin >> n >> q;
    for (int i=0; i<n-1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edge[u].eb(v, w);
        edge[v].eb(u, w);
    }

    CentroidDecomposition();
    pary(pG+1, pG+1+n);
    while (q--) {
        int cmd, u, k;
        cin >> cmd >> u;
        //debug(cmd, u);
        if (cmd == 1) {
            chg(u, true);
        } else if (cmd == 2) {
            chg(u, false);
        } else {
            cin >> k;
            cout << kth(u, k) << endl;
        }

#ifdef tmd
        for (int i=1; i<=n; i++) {
            debug(tp[i]);
        }
        for (int i=1; i<=n; i++) {
            debug(tc[i]);
        }
#endif
    }

    return 0;
}

/*
7 20
3 7 10
6 5 4
1 3 3
1 4 6
4 2 9
6 7 9
1 6
1 1
1 4
2 6
1 2
1 7
3 2 4

 */
