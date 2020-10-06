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

int n;
vector<vector<pii> > edge;
struct CentroidDecomp {
    struct Info {
        ll dis=0, sz=0, mi=0;
    };
    vector<Info> info;
    vector<int> dead, dep, anc, vis, sz;
    vector<vector<ll> > dis;

    CentroidDecomp () : info(n), dead(n), dep(n), anc(n), vis(n), sz(n) {
        int lgg = __lg(n) + 2;
        dis.resize(lgg, vector<ll>(n, 0));
        build(0, 0, -1);
    }

    int center (int nd) {
        vector<int> que = {nd};
        vis[nd] = true;
        int hd = 0;
        while (hd < SZ(que)) {
            int cur = que[hd++];
            for (auto e : edge[cur]) {
                if (!vis[e.X] && !dead[e.X]) {
                    que.eb(e.X);
                    vis[e.X] = true;
                }
            }
        }
        reverse(ALL(que));

        int cen = -1;
        for (int v : que) {
            sz[v] = 1;
            vis[v] = false;
            bool flag = true;
            for (auto e : edge[v]) {
                if (!dead[e.X] && !vis[e.X]) {
                    sz[v] += sz[e.X];
                    flag &= sz[e.X] * 2 <= SZ(que);
                }
            }
            flag &= sz[v] * 2 >= SZ(que);
            if (flag) cen = v;
        }
        return cen;
    }

    void build (int nd, int d, int rt) {
        int cen = center(nd);
        debug(nd, rt, cen);
        assert(cen != -1);
        dead[cen] = true;
        dep[cen] = d;
        anc[cen] = rt;

        vector<int> que = {cen};
        int hd = 0;
        while (hd < SZ(que)) {
            int cur = que[hd++];
            for (auto e : edge[cur]) {
                if (!vis[e.X] && !dead[e.X]) {
                    que.eb(e.X);
                    vis[e.X] = true;
                    dis[d][e.X] = dis[d][cur] + e.Y;
                }
            }
        }
        for (int v : que) vis[v] = false;

        for (auto e : edge[cen]) {
            if (!dead[e.X]) {
                build(e.X, d+1, cen);
            }
        }
    }

    void upd (int nd) {
        for (int x=nd; x!=-1; x=anc[x]) {
            info[x].dis += dis[dep[x]][nd];
            info[x].sz += 1;
            if (anc[x] != -1) info[x].mi += dis[dep[x]-1][nd];
        }
    }

    ll qry (int nd) {
        ll res = info[nd].dis;
        for (int x=nd; anc[x]!=-1; x=anc[x]) {
            res += dis[dep[x]-1][nd] * (info[anc[x]].sz - info[x].sz);
            res += info[anc[x]].dis;
            res -= info[x].mi;
        }
        return res;
    }
};
signed main () {
    TIME(main);
    IOS();

    int q;
    cin >> n >> q;

    edge.resize(n);
    for (int i=0; i<n-1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edge[u].eb(v, w);
        edge[v].eb(u, w);
    }

    CentroidDecomp cd;
    vector<int> vis(n);
    for (int i=0; i<q; i++) {
        int t, x;
        cin >> t >> x;

        if (t == 1) {
            if (!vis[x]) cd.upd(x);
            vis[x] = true;
        } else {
            cout << cd.qry(x) << endl;
        }
    }

    return 0;
}

