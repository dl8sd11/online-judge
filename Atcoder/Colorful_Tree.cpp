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

typedef pair<int,int> pii;
pii bit[MAXN];

void operator += (pii &a, const pii &b) {
    a.first += b.first;
    a.second += b.second;
}
void add (int x, pii val) {
    for (x++; x<MAXN; x+=-x&x) {
        bit[x] += val;
    }
}

pii qry (int x) {
    pii ret = {0, 0};
    for (x++; x>0; x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

pii qry (int l, int r) {
    pii retr = qry(r), retl = qry(l-1);
    return {retr.first-retl.first, retr.second-retl.second};
}

struct CEdge {
    int u, v, d;
};
vector<CEdge> cedge[MAXN];

struct Query {
    int u, v, d, qid;
};
vector<Query> query[MAXN];

int n, q, ans[MAXN];
vector<int> edg[MAXN];

int dep[MAXN], sz[MAXN], son[MAXN], tp[MAXN], anc[MAXN], in[MAXN], tim;

void dfs_pre (int nd, int par) {
    dep[nd] = dep[par] + 1;
    sz[nd] = 1;
    son[nd] = 0;
    anc[nd] = par;
    for (auto v : edg[nd]) {
        if (v != par) {
            dfs_pre(v, nd);
            sz[nd] += sz[v];
            if (sz[v] > sz[son[nd]]) {
                son[nd] = v;
            }
        }
    }
}

void dfs_hld (int nd, int hd) {
    in[nd] = tim++;
    tp[nd] = hd;
    if (son[nd]) {
        dfs_hld(son[nd], hd);
    }
    for (auto v : edg[nd]) {
        if (v != anc[nd] && v != son[nd]) {
            dfs_hld(v, v);
        }
    }
}

void addw (int nd, int w) {
    add(in[nd], {w, w>0 ? 1 : -1});
}


pii qryw (int u, int v) {
    pii ret = {0, 0};
    while (tp[u] != tp[v]) {
        if (dep[tp[u]] > dep[tp[v]]) {
            swap(u, v);
        }
        ret += qry(in[tp[v]], in[v]);
        v = anc[tp[v]];
    }
    if (dep[v] > dep[u]) {
        swap(u, v);
    }
    ret += qry(in[v]+1, in[u]);
    return ret;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> q;
    REP (i, n-1) {
        int u, v, c, d;
        cin >> u >> v >> c >> d;
        edg[u].emplace_back(v);
        edg[v].emplace_back(u);
        cedge[c].push_back({u, v, d});
    }

    REP (i, q) {
        int u, v, c, d;
        cin >> c >> d >> u >> v;
        query[c].push_back({u, v, d, i});
    }
    debug("inputed");

    dfs_pre(1, 1);
    dfs_hld(1, 1);

    debug("prebuilt");

    REP1 (i, n-1) {
        for (auto &E : cedge[i]) {
            if (dep[E.u] > dep[E.v]) {
                swap(E.u, E.v);
            }
            addw(E.v, E.d);
        }
    }

    REP1 (i, n-1) {
        for (const auto &E : query[i]) {
            pii ret = qryw(E.u, E.v);
            debug(E.u, E.v, ret.first);
            ans[E.qid] = ret.first;
        }
    }

    REP1 (i, n-1) {
        for (const auto &E : cedge[i]) {
            addw(E.v, -E.d);
        }
    }

    REP1 (i, n-1) {
        for (const auto &E : cedge[i]) {
            addw(E.v, E.d);
        }

        for (const auto &Q : query[i]) {
            pii ret = qryw(Q.u, Q.v);
            debug(Q.u, Q.v, ret.first, ret.second);
            ans[Q.qid] += Q.d * ret.second - ret.first;
        }

        for (const auto &E : cedge[i]) {
            addw(E.v, -E.d);
        }
    }

    REP (i, q) {
        cout << ans[i] << endl;
    }
    return 0;
}
