#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
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

bool is_anc (int a, int s) {
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
vector<SQuery> sq[MAXN];

ll ans[MAXN];

void solve_small () {
    init();

    int ptr =  0;
    REP (i, MAXN) {
        for (auto qu : sq[i]) {
            if (qu.x == 4 && qu.p == 1) {
                debug(qu.id, qu.v, i);
            }
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

const int K = 3;

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
Node *root[MAXN];

Node *mrg (Node *a, Node *b) {
//    debug(a, b);
    if (!a || !b) {
        return a ? a : b;
    } else {
        if (a->pri > b->pri) {
            a->push();
            assert(a->r != a);
            a->r = mrg(a->r, b);
            return a;
        } else {
            b->push();
            assert(b->l != b);
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
    debug(rin[nd->key]);
    nd->push();
    val[rin[nd->key]] += nd->v;

    if (nd->l) {
        dfs_push(nd->l);
    }
    if (nd->r) {
        dfs_push(nd->r);
    }
    delete(nd);
}

void dfs_dbug (Node *nd) {
    if (!nd) {
        return;
    }
    debug(nd->key);
    dfs_dbug(nd->l);
    dfs_dbug(nd->r);
}

vector<Modify> queued;
void rebuild () {
    init();

    REP1 (i, n) {
        root[i] = new Node{0,0,in[i],0,0,rand()};
    }

    pary(in+1, in+1+n);
    pary(out+1, out+1+n);

    sort(queued.begin(), queued.end());

    int ptr = 0;
    for (Modify md : queued) {
        while (ptr < n-1 && edges[ptr].w < md.y) {
            int xp = rt[fnd(edges[ptr].u)];
            debug(ptr, edges[ptr].u, edges[ptr].v, xp, edges[ptr].w);

            Node *l, *r;
//            debug(root[xp]->key);
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
            debug(i);
            dfs_push(root[i]);
        }
    }

    queued.clear();
}

/*********************GoodLuck***********************/
int main () {
    IOS();

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
            debug(queued.size());
           if (queued.size() >= K) {
               rebuild();
           }

            for (auto m : queued) {
                if (is_anc(m.v, v)) {
                    sq[m.y].push_back({v, m.v, m.x, qcnt});
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

    solve_small();

    REP (i, qcnt) {
        cout << ans[i] << endl;
    }
}
