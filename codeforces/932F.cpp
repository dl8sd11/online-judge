#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
typedef complex<ll> point;

int n, a[MAXN], b[MAXN];
vector<int> edg[MAXN];
ll dp[MAXN];

ll dot (const point &a, const point &b) {
    return (conj(a)*b).real();
}

ll f (const point &a, ll x) {
    return dot(a, {x, 1});
}

struct Tree {
    vector<int> nodes;
    struct Node {
        int l, r;
        Node *lc, *rc;
        point fun;
        Node (int L, int R) :l(L), r(R), lc(nullptr), rc(nullptr), fun({0, INF}){}
    };
    Node *root;

    Tree () {
        root = new Node(-MAXN, MAXN);
    }

    void add_line (point nw, Node *nd) {
        int l = nd->l ,r = nd->r;
        int m = (l + r) >> 1;
        bool lef = f(nw, l) < f(nd->fun, l);
        bool mid = f(nw, m) < f(nd->fun, m);
        if (mid) {
            swap(nw, nd->fun);
        }
        if (r == l + 1) {
            return;
        } else if (mid != lef) {
            if (!nd->lc) {
                nd->lc = new Node(l, m);
            }
            add_line(nw, nd->lc);
        } else {
            if (!nd->rc) {
                nd->rc = new Node(m, r);
            }
            add_line(nw, nd->rc);
        }
    }

    ll qry (int x, Node *nd) {
        if (!nd) {
            return INF;
        }
        int m = (nd->l + nd->r) >> 1;
        if (x >= m) {
            return min(qry(x, nd->rc), f(nd->fun, x));
        } else {
            return min(qry(x, nd->lc), f(nd->fun, x));
        }
    }

    void add (int nd) {
        add_line(point(b[nd],dp[nd]), root);
        nodes.emplace_back(nd);
    }
} cht[MAXN];

void mrg (Tree &ta, Tree &tb, bool db=false) {
    if (SZ(ta.nodes) < SZ(tb.nodes)) {
        swap(ta, tb);
    }

    for (auto nd : tb.nodes) {
        ta.add(nd);
    }
}

void dfs (int nd, int par) {
    for (auto v : edg[nd]) {
        if (v != par) {
            dfs(v, nd);
            mrg(cht[nd], cht[v], nd==1);
        }
    }

    if (nd == par || SZ(edg[nd]) != 1) {
        dp[nd] = cht[nd].qry(a[nd], cht[nd].root);
    }
    cht[nd].add(nd);
    if (nd == 2) {
        ll ret = cht[nd].qry(5, cht[nd].root);
        debug(ret);
    }
}

/*
3
5 -10 7
-8 -80 -10
1 2
2 3

*/
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP1 (i,n) {
        cin >> a[i];
    }
    REP1 (i,n) {
        cin >> b[i];
    }
    REP (i,n-1) {
        int u, v;
        cin >> u >> v;
        edg[u].emplace_back(v);
        edg[v].emplace_back(u);
    }

    dfs(1, 1);
    REP1 (i, n) {
        cout << dp[i] << " \n"[i==n];
    }
    return 0;
}
