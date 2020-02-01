#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<(k) ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=(k) ; i-=in)
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

const int MAXN = 100005;
const ll MOD = 1000000007;

int n, q;
ll val[MAXN];
int djs[MAXN], rt[MAXN], sz[MAXN];

void init () {
    REP1 (i, n) {
        rt[i] = djs[i] = i;
        sz[i] = 1;
    }
}

int fnd (int x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

void uni (int x, int y) { // make x root
    x = fnd(x), y = fnd(y);
    int rrt = rt[x];
    if (sz[x] > sz[y]) {
        swap(x, y);
    }
    djs[x] = y;
    rt[y] = rrt;
    sz[y] += sz[x];
}


vector<int> G[MAXN];
int in[MAXN], out[MAXN], dfn, rin[MAXN];

void build_time (int nd, int par) {
    rin[dfn] = nd;
    in[nd] = dfn++;
    for (auto v : G[nd]) {
        if (v != par) {
            build_time(v, nd);
        }
    }
    out[nd] = dfn;
}

inline bool is_anc (int a, int s) {
    return in[a] <= in[s] && out[s] <= out[a];
}

struct Edge {
    int u, v, w;

    bool operator < (const Edge &oth) const {
        return w < oth.w;
    }
} edges[MAXN];


struct Modify {
    int x, y, v;
    bool operator < (const Modify &oth) const {
        return y < oth.y;
    }
};

struct SQuery {
    int x, p, v, id;
};
vector<SQuery> sq;
vector<int> bk[MAXN];

ll ans[MAXN];

void solve_small () {
    init();

    int ptr =  0;

    REP (i, MAXN) {

        for (auto idx : bk[i]) {
            const SQuery &qu = sq[idx];
            if (fnd(qu.x) == fnd(qu.p)) {
                ans[qu.id] += qu.v;
            }
        }

        while (ptr < n-1 && edges[ptr].w == i) {
            uni(edges[ptr].u, edges[ptr].v);
            ptr++;
        }
    }

}

const int K = 1569;//3;

struct Node {
    Node *l, *r;
    int key;
    ll v, tag;
    int pri;

    void push () {
        v += tag;
        if (l) {
            l->tag += tag;
        }
        if (r) {
            r->tag += tag;
        }
        tag = 0;
    }
};
Node *root[MAXN], pool[MAXN];

Node *mrg (Node *a, Node *b) {
    if (!a || !b) {
        return a ? a : b;
    } else {
        if (a->pri > b->pri) {
            a->push();
            a->r = mrg(a->r, b);
            return a;
        } else {
            b->push();
            b->l = mrg(a, b->l);
            return b;
        }
    }
}

void split (Node *o, Node *&a, Node *&b, int k) { // r >= k
    if (!o) {
        a = b = 0;
        return;
    } else {
        o->push();
        if (o->key >= k) {
            b = o;
            split(b->l, a, b->l, k);
        } else {
            a = o;
            split(a->r, a->r, b, k);
        }
    }
}

void dfs_push (Node *nd) {
    nd->push();
    val[rin[nd->key]] += nd->v;

    if (nd->l) {
        dfs_push(nd->l);
    }
    if (nd->r) {
        dfs_push(nd->r);
    }
}


vector<Modify> queued;


void rebuild () {
    init();

    REP1 (i, n) {
        pool[i] = Node{0,0,in[i],0,0,rand()};
        root[i] = &pool[i];
    }

    sort(queued.begin(), queued.end());

    int ptr = 0;
    for (const Modify &md : queued) {
        while (ptr < n-1 && edges[ptr].w < md.y) {
            int xp = rt[fnd(edges[ptr].u)];

            Node *l, *r;
            split(root[xp], l, r, in[edges[ptr].v]);


            root[xp] = mrg(l, mrg(root[edges[ptr].v], r));

            uni(edges[ptr].u, edges[ptr].v);
            ptr++;
        }

        int r = rt[fnd(md.v)];
        Node *L, *M, *R;
        split(root[r], L, M, in[md.v]);
        split(M, M, R, out[md.v]);

        M->tag += md.x;

        root[r] = mrg(L, mrg(M, R));
    }

    REP1 (i, n) {
        if (rt[fnd(i)] == i) {
            dfs_push(root[i]);
        }
    }

    queued.clear();
}

/*********************GoodLuck***********************/
int main () {
    IOS();
    TIME(man);

    cin >> n >> q;
    REP1 (i, n) {
        cin >> val[i];
    }


    REP (i, n - 1) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].w = (MAXN-1) - edges[i].w;

        G[edges[i].u].emplace_back(edges[i].v);
        G[edges[i].v].emplace_back(edges[i].u);
    }
    sort(edges, edges+n-1);
    build_time(1, -1);


    REP (i, n-1) {
        if (is_anc(edges[i].v, edges[i].u)) {
            swap(edges[i].v, edges[i].u);
        }
    }

//    srand(time(0));

    int qcnt = 0;

    REP (i, q) {
        int cmd, x, y, v;
        cin >> cmd;

        if (cmd == 1) {
            cin >> v;

           if (queued.size() >= K) {
               rebuild();
           }

            for (auto m : queued) {
                if (is_anc(m.v, v)) {
                    bk[m.y].emplace_back(sq.size());
                    sq.push_back({v, m.v, m.x, qcnt});
                }
            }

            ans[qcnt] += val[v];
            qcnt++;
        } else {
            cin >> x >> y >> v;
            y = (MAXN-1) - y + 1;
            queued.push_back({x, y, v});
        }
    }

    {
        TIME(SM);
        solve_small();
    }

    debug(qcnt);
    #ifndef tmdd

    REP (i, qcnt) {
        cout << ans[i] << endl;
    }
    #endif
}
