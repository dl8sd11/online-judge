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
const ll MAXN = 5e5 + 5;

vector<pair<int,int>> tree;
vector<int> edge[MAXN];

vector<int> nid, in, out, dep;
void dfs (int nd, int par, int dp=0) {
    dep[nd] = dp;
    in[nd] = SZ(nid);
    nid.eb(nd);
    for (int v : edge[nd]) {
        if (v != par) {
            dfs(v, nd, dp+1);
            nid.eb(nd);
        }
    }
    out[nd] = SZ(nid);
}

struct Node {
    int one[2];
    int mid;
    int lf[2];
    int rt[2];
    int ans;
    Node () {
        ans = mid = one[0] = one[1] = lf[0] = lf[1] = rt[0] = rt[1] = -iNF;
    }
};

Node seg[MAXN*8];

Node mrg (const Node &n1, const Node &n2) {
    Node ret;
    for (int i=0; i<2; i++) {
        ret.one[i] = max(n1.one[i], n2.one[i]);
        ret.mid = max(n1.mid, n2.mid);
        ret.lf[i] = max({n1.lf[i], n2.lf[i], n1.one[i]+n2.mid});
        ret.rt[i] = max({n1.rt[i], n2.rt[i], n1.mid+n2.one[i]});
        ret.ans = max({ret.ans, n1.ans, n2.ans, n1.lf[i]+n2.one[i], n1.one[i]+n2.rt[i]});
    }
    return ret;
}

bool tag[MAXN*8];

Node get (int o) {
    Node ret = seg[o];
    if (tag[o]) {
        swap(ret.one[0], ret.one[1]);
        swap(ret.lf[0], ret.lf[1]);
        swap(ret.rt[0], ret.rt[1]);
    }
    return ret;
}

void pull (int nd) {
    seg[nd] = mrg(get(nd<<1), get(nd<<1|1));
}

void push (int nd) {
    if (tag[nd]) {
        seg[nd] = get(nd);
        tag[nd<<1] ^= 1;
        tag[nd<<1|1] ^= 1;
    }
    tag[nd] = 0;
}

void build (int o, int l, int r) {
    if (r == l + 1) {
        //debug(l, dep[nid[l]]);
        seg[o].one[0] = dep[nid[l]];
        seg[o].mid = -2 * dep[nid[l]];
        seg[o].lf[0] = seg[o].rt[0] = -dep[nid[l]];
    } else {
        int mid = (l + r) >> 1;
        build(o<<1, l, mid);
        build(o<<1|1, mid, r);
        pull(o);
        //debug(o,l,r, seg[o].one[0], seg[o].lf[0], seg[o].ans);
    }
}

void flp (int qL, int qR, int o, int nL, int nR) {
    if (qL >= qR || qL >= nR || qR <= nL) {
        return;
    } else if (qL <= nL && nR <= qR) {
        tag[o] ^= 1;
    } else {
        push(o);
        int nM =(nL + nR) >> 1;
        flp(qL, qR, o<<1, nL, nM);
        flp(qL, qR, o<<1|1, nM, nR);
        pull(o);
    }

}

int sz;
void tog (int id) {
    int u, v;
    tie(u, v) = tree[id];
    if (dep[u] > dep[v]) swap(u, v);
    flp(in[v], out[v], 1, 0, sz);
}
signed main () {
    TIME(main);
    IOS();

    int n;
    cin >> n;
    in.resize(n);
    out.resize(n);
    dep.resize(n);

    vector<int> init;
    for (int i=0; i<n-1; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        u--, v--;
        edge[u].eb(v);
        edge[v].eb(u);
        tree.eb(u, v);
        if (t) init.eb(i);
    }

    dfs(0, -1);
    debug(seg[1].ans);

    sz  = SZ(nid);
    build(1, 0, sz);
    for (auto v : init) {
        tog(v);
    }

    int q;
    cin >> q;
    while (q--) {
        int eid;
        cin >> eid;
        tog(eid-1);

        cout << seg[1].ans << endl;
    }
    return 0;
}
