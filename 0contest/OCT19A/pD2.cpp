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

const int MAXN = 500005;
const int K = 702;
const int MAXLG = __lg(MAXN) + 3;
const ll MOD = 1000000007;

namespace BIT{
    ll bit[MAXN*2];
    void add (int p, ll val) {
        for (p+=MAXN; p<MAXN*2; p+=-p&p) {
            bit[p] += val;
        }
    }

    ll qry (int p) {
        ll ret = 0;
        for (p+=MAXN; p>0; p-=-p&p) {
            ret += bit[p];
        }
        return ret;
    }
}

int n, Q, dep[MAXN];
vector<int> edg[MAXN];
bool is_leaf[MAXN];
ll ans[MAXN];

void dfs_pre (int nd, int par) {
    dep[nd] = dep[par] + 1;

    for (auto v : edg[nd]) {
        if (v != par) {
            dfs_pre(v, nd);
        }
    }

    if ((nd != par && SZ(edg[nd]) == 1) || n == 1) {
        is_leaf[nd] = true;
    }
}

void add_edge (int u, int v) {
    edg[u].emplace_back(v);
    edg[v].emplace_back(u);
}

struct Query {
    bool type;
    int v, k, t;
};
vector<Query> query[MAXN];

void solve (int nd, int par) {
    for (auto q : query[nd]) {
        if (q.type) {
            if (is_leaf[nd]) {
                ans[q.k] = BIT::qry(dep[nd]) - BIT::qry(dep[nd]-q.t-1);
            } else {
                ans[q.k] = BIT::qry(dep[nd]-q.t) - BIT::qry(dep[nd]-q.t-1);
            }
        } else {
            BIT::add(dep[nd]-q.t, q.k);
        }
    }

    for (auto v : edg[nd]) {
        if (v != par) {
            solve(v, nd);
        }
    }

    for (auto q : query[nd]) {
        if (!q.type) {
            BIT::add(dep[nd]-q.t, -q.k);
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> Q;
    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }
    REP1 (i, n) {
        int a;
        cin >> a;
        query[i].push_back({0, i, a, 0});
    }

    dfs_pre(1, 1);

    int qcnt = 0;
    REP1 (rd, Q) {
        char cmd;
        int v, k;
        cin >> cmd >> v;
        if (cmd == '+') {
            cin >> k;
            query[v].push_back({0, v, k, rd});
        } else {
            query[v].push_back({1, v, qcnt++, rd});
        }
    }

    solve(1, 1);

    REP (i, qcnt) {
        cout << ans[i] << endl;
    }
    return 0;
}
