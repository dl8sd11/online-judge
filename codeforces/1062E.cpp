#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<int, ll> pli;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#ifdef tmd
#define TIME(i) Timer i(#i)
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<" ,";_do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s,const pair<_a,_b> &_p){return _s<<"("<<_p.X<<","<<_p.Y<<")";}
template<typename It> ostream& _OUTC(ostream &_s,It _ita,It _itb)
{
    _s<<"{";
    for(It _it=_ita;_it!=_itb;_it++)
    {
        _s<<(_it==_ita?"":",")<<*_it;
    }
    _s<<"}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s,vector<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,set<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif
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

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 100005;
const ll MAXLG = __lg(MAXN) + 3;

int n, q, dep[MAXN], anc[MAXLG][MAXN];
vector<int> edge[MAXN];


void dfs (int nd, int par) {
    dep[nd] = dep[par] + 1;
    anc[0][nd] = par;
    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v, nd);
        }
    }
}

void build_lca () {
    REP1 (i, MAXLG - 1) {
        REP1 (j, n) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }
}

int get_lca(int u, int v) {
    if (dep[u] > dep[v]) {
        swap(u, v);
    }
    RREP (i, MAXLG - 1) {
        if (dep[anc[i][v]] >= dep[u]) {
            v = anc[i][v];
        }
    }
    if (u == v) {
        return u;
    }

    RREP (i, MAXLG - 1) {
        if (anc[i][u] != anc[i][v]) {
            u = anc[i][u];
            v = anc[i][v];
        }
    }
    return anc[0][u];
}
typedef array<pii, 2> ppp; // [{lca, rm},{}]
typedef pair<ppp, int> dt;
dt mrg (const dt &l, const dt &r) {
    dt R;
    ppp &ret = R.X;
    R.Y = get_lca(l.Y, r.Y);
    REP (i, 2) {
        if (l.X[i].X != 0)  {
            int lC = get_lca(l.X[i].X, r.Y);
            if (dep[lC] > dep[ret[0].X]) {
                ret[1] = ret[0];
                ret[0] = pii(lC, l.X[i].Y);
            } else if (dep[lC] > dep[ret[1].X]) {
                ret[1] = pii(lC, l.X[i].Y);
            }
        } else {
            int lC = r.Y;
            if (dep[lC] > dep[ret[0].X]) {
                ret[1] = ret[0];
                ret[0] = pii(lC, l.X[i].Y);
            } else if (dep[lC] > dep[ret[1].X]) {
                ret[1] = pii(lC, l.X[i].Y);
            }
        }
    }
    REP (i, 2) {
        if (r.X[i].X != 0)  {
            int lC = get_lca(r.X[i].X, l.Y);
            if (dep[lC] > dep[ret[0].X]) {
                ret[1] = ret[0];
                ret[0] = pii(lC, r.X[i].Y);
            } else if (dep[lC] > dep[ret[1].X]) {
                ret[1] = pii(lC, r.X[i].Y);
            }
        } else {
            int lC = l.Y;
            if (dep[lC] > dep[ret[0].X]) {
                ret[1] = ret[0];
                ret[0] = pii(lC, r.X[i].Y);
            } else if (dep[lC] > dep[ret[1].X]) {
                ret[1] = pii(lC, r.X[i].Y);
            }
        }
    }
    return R;
}

struct Node {
    int l, r;
    Node *lc, *rc;
    dt can;

    void pull () {
        can = mrg(lc->can, rc->can);
    }
};
Node *root;

Node *build (int l, int r) {
    if (l == r - 1) {
        ppp cp = {pii(0, l+1), pii(0, l+1)};
        dt cur = dt(cp, l+1);
        return new Node{l, r, nullptr, nullptr, cur};
    } else {
        int m = (l + r) >> 1;
        Node *ret = new Node{l, r, build(l, m), build(m, r), dt()};
        ret->pull();
        return ret;
    }
}

dt qry (int l, int r, Node *nd) {
    if (l == nd->l && r == nd->r) {
        return nd->can;
    } else {
        int md = (nd->l + nd->r) >> 1;
        if (l >= md) {
            return qry(l, r, nd->rc);
        } else if (r <= md) {
            return qry(l, r, nd->lc);
        } else {
            return mrg(qry(l, md, nd->lc), qry(md, r, nd->rc));
        }
    }
}
/********** Good Luck :) **********/
int main()
{
    TIME(main);
    IOS();
    dep[0] = -1;

    cin >> n >> q;
    for (int i=2; i<=n; i++) {
        int j;
        cin >> j;
        edge[i].eb(j);
        edge[j].eb(i);
    }

    dfs(1, 0);
    build_lca();

    root = build(0, n);
    while (q--) {
        int u, v;
        cin >> u >> v;
        dt ret = qry(u-1, v, root);
        cout << ret.X[0].Y << " " << dep[ret.X[0].X] << endl;
    }
    return 0;
}
