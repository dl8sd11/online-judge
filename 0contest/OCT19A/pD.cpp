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

const int MAXN = 1000006;
const int K = 702;
const int MAXLG = __lg(MAXN) + 3;
const ll MOD = 1000000007;

namespace BIT{
    ll bit[MAXN];
    void add (int p, ll val) {
        for (p++; p<MAXN; p+=-p&p) {
            bit[p] += val;
        }
    }

    ll qry (int p) {
        ll ret = 0;
        for (p++; p>0; p-=-p&p) {
            ret += bit[p];
        }
        return ret;
    }
}

int n, q, dep[MAXN], anc[MAXLG][MAXN], hd[MAXN], sz[MAXN], son[MAXN], in[MAXN];
vector<int> edg[MAXN];
bool is_leaf[MAXN];
ll a[MAXN];

void dfs_pre (int nd, int par) {
    dep[nd] = dep[par] + 1;
    anc[0][nd] = par;
    sz[nd] = 1;
    son[nd] = 0;

    for (auto v : edg[nd]) {
        if (v != par) {
            dfs_pre(v, nd);
            sz[nd] += sz[v];
            if (sz[v] >= sz[son[nd]]) {
                son[nd] = v;
            }
        }
    }

    if (nd != par && SZ(edg[nd]) == 1) {
        is_leaf[nd] = true;
    }
}

int tt;
void dfs_hd (int nd, int par, int tp) {
    hd[nd] = tp;
    in[nd] = tt++;
    if (son[nd]) {
        dfs_hd(son[nd], nd, tp);
    }
    for (auto v : edg[nd]) {
        if (v != son[nd] && v != par) {
            dfs_hd(v, nd, v);
        }
    }
}

void add_edge (int u, int v) {
    edg[u].emplace_back(v);
    edg[v].emplace_back(u);
}

void build_anc () {
    REP1 (i, MAXLG-1) {
        REP1 (j, MAXN-1) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }
}

int kth_anc (int nd, int k) {
    int ret = nd;
    for (int i=MAXLG-1; i>=0; i--) {
        if (dep[nd] - dep[anc[i][ret]] <= k) {
            ret = anc[i][ret];
        }
    }
    return ret;
}

void add (int v, ll val) {
    a[v] += val;
    BIT::add(in[v], val);
}

ll qry (int v, int hei) {
    ll ret = 0;
    int bs = v;
    while (dep[bs] - dep[hd[v]] < hei) {
        ret += BIT::qry(in[v]) - BIT::qry(in[hd[v]]-1);
        v = anc[0][hd[v]];
    }
    return ret + BIT::qry(in[v]) - BIT::qry(in[kth_anc(bs, hei)]-1);
}

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> q;
    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }
    REP1 (i, n) {
        cin >> a[i];
    }

    int root = 1;
    REP (i, q) {
        add_edge(root, i+n+1);
        root = i+n+1;
    }

    dfs_pre(root, root);
    dfs_hd(root, root, root);
    build_anc();

    REP1 (rd, q) {
        char cmd;
        int v, k;
        cin >> cmd >> v;
        debug(kth_anc(v, rd));
        if (cmd == '+') {
            cin >> k;
            add(kth_anc(v, rd), k);
        } else {
            if (is_leaf[v]) {
                cout << qry(v, rd) << endl;
            } else {
                cout << a[kth_anc(v, rd)] << endl;
            }
        }
    }
    return 0;
}
