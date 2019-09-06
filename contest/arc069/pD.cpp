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
const ll MAXN = 10004;

int n;
int p[MAXN][2], ccnt, cc[MAXN * 8], vid[MAXN * 2];
bool vis[MAXN * 8];
vector<int> topo;

vector<int> edg[MAXN * 8], rev[MAXN * 8];

void dfs1 (int nd) {
    vis[nd] = true;
    for (auto v : rev[nd]) {
        if (!vis[v]) {
            dfs1(v);
        }
    }
    topo.eb(nd);
}

void dfs2 (int nd) {
    cc[nd] = ccnt;
    vis[nd] = false;
    for (auto v : edg[nd]) {
        if (vis[v]) {
            dfs2(v);
        }
    }
}

void add_edge (int f, int t) {
    edg[f].eb(t);
    rev[t].eb(f);
}

int nid[MAXN * 2], ncnt;
struct Node {
    int l, r, id;
    Node *lc, *rc;
};


Node *build (int l, int r) {
    if (r == l + 1) {
        return new Node{l, r, ncnt++, nullptr, nullptr};
    } else {
        int mid = (l + r) >> 1;
        return new Node{l, r, ncnt++, build(l, mid), build(mid, r)};
    }
}

Node *root;

void build_tree (Node *nd) {
    // debug(nd->id, nd->l, nd->r);
    if (nd->l == nd->r - 1) {
        nid[nd->l] = nd->id;
    } else {
        assert(nd->lc);
        add_edge(nd->lc->id, nd->id);
        add_edge(nd->rc->id, nd->id);
        debug(nd->lc->id, nd->id);
        debug(nd->rc->id, nd->id);
        build_tree(nd->lc);
        build_tree(nd->rc);
    }
}
void build_edge (int l, int r, int id, Node *nd = root) {
    if (r <= l) {
        return;
    } else if (l == nd->l && r == nd->r) {
        debug(nd->id, nid[id]);
        add_edge(nd->id, nid[id]);
    } else {
        int mid = (nd->l + nd->r) >> 1;
        if (l >= mid) {
            build_edge(l, r, id, nd->rc);
        } else if (r <= mid) {
            build_edge(l, r, id, nd->lc);
        } else {
            build_edge(l, mid, id, nd->lc);
            build_edge(mid, r, id, nd->rc);
        }
    }
}

vector<pii> val;
void build_graph (int pos, int f, int t, int d) {
    int lb = lower_bound(ALL(val), pii(pos-d+1, -iNF))-val.begin();
    int ub = lower_bound(ALL(val), pii(pos+d-1, iNF))-val.begin();

    debug(pos);
    build_edge(lb, f, t);
    debug(lb, f, t);
    build_edge(f+1, ub, t);
    debug(f+1, ub, t);
}

bool solve (int d) {
    REP (i, ncnt) {
        edg[i].clear();
        rev[i].clear();
    }

    build_tree(root);
    REP (i, n) {
        build_graph(p[i][0], vid[i<<1], vid[i<<1|1], d);
        build_graph(p[i][1], vid[i<<1|1], vid[i<<1], d);
    }

    // int l, r, id;
    // while (cin >> l >> r >> id) {
    //     build_edge(l, r, id);
    // }


    MEM(vis, 0);
    topo.clear();

    debug(ncnt);
    REP (i, ncnt) {
        if (!vis[i]) {
            dfs1(i);
        }
    }
    debug(topo);
    debug(edg[10]);
    for (int i=SZ(topo)-1; i>=0; i--) {
        if (vis[topo[i]]) {
            dfs2(topo[i]);
            ccnt++;
        }
    }
    pary(cc, cc+ncnt);
    REP (i, n) {
        debug(nid[vid[i<<1]], nid[vid[i<<1|1]]);
        if (cc[nid[vid[i<<1]]] == cc[nid[vid[i<<1|1]]]) {
            debug(i);
            return false;
        }
    }

    return true;
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n;

    REP (i, n) {
        cin >> p[i][0] >> p[i][1];
        val.eb(p[i][0], i<<1);
        val.eb(p[i][1], i<<1|1);

    }
    sort(ALL(val));
    REP (i, SZ(val)) {
        vid[val[i].Y] = i;
    }
    debug(val);

    root = build(0, n*2);

    bool re = solve(4);
    debug(re);
    int l = iNF, r = -iNF;

    REP (i, n) {
        REP (j, i) {
            REP (s1, 2) {
                REP (s2, 2) {
                    l = min(l, abs(p[i][s1] - p[j][s2]));
                    r = max(r, abs(p[i][s1] - p[j][s2]));
                }
            }
        }
    }
    r++;
    while (l < r - 1) {
        int mid = (l + r) >> 1;
        if (solve(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << l << endl;

    return 0;
}

/*
1 4 1
0 1 0
*/

/*
3
5 9
8 3
7 7
1 4 0
0 1 5
3 6 3
4 6 2

*/