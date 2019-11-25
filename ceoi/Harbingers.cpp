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

typedef pair<ll,ll> pll;

int n;
vector<pair<int,ll> > edge[MAXN];
ll dp[MAXN], S[MAXN], V[MAXN], p[MAXN], dep[MAXN];


struct Vec {
    ll x, y;
    ll eval (ll pos) {
        return pos*x + y;
    }
};

struct Node {
    int l, r;
    Node *lc, *rc;
    Vec bst;

    Node (int _l, int _r) : l(_l), r(_r) {
        lc = rc = nullptr;
        bst = {0, INF};
    }
};
Node *root[MAXN];

Node *addLine (Vec nw, Node *nd) {
    int mid = (nd->l + nd->r) >> 1;
    bool lnw = nw.eval(nd->l) < nd->bst.eval(nd->l);
    bool mnw = nw.eval(mid) < nd->bst.eval(mid);

    Node *ret = new Node(*nd);
    if (mnw) {
        swap(nw, ret->bst);
    }
    if (ret->l == ret->r - 1) {
        return ret;
    } else if (lnw != mnw) { // left
        if (!ret->lc) {
            ret->lc = new Node(ret->l, mid);
        }
        ret->lc = addLine(nw, ret->lc);
    } else {
        if (!ret->rc) {
            ret->rc = new Node(mid, ret->r);
        }
        ret->rc = addLine(nw, ret->rc);
    }

    return ret;
}

ll eval (ll x, Node *nd) {
    if (!nd) {
        return INF;
    }
    ll ret = nd->bst.eval(x);
    int mid = (nd->l + nd->r) >> 1;
    if (x >= mid) {
        ret = min(ret, eval(x, nd->rc));
    } else {
        ret = min(ret, eval(x, nd->lc));
    }
    return ret;
}
// dp[nd] = dp[x] + dep[nd]*V[nd] - dep[x]*V[nd] + S[nd]

int cnt;
void dfs (int nd, int par) {
    if (nd != 1) {
        dp[nd] = dep[nd]*V[nd] + eval(V[nd], root[par]) + S[nd];
    }
    root[nd] = addLine({-dep[nd], dp[nd]}, root[par]);

    for (auto v : edge[nd]) {
        if (v.first != par) {
            p[v.first] = nd;
            dep[v.first] = dep[nd] + v.second;
            dfs(v.first, nd);
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();
//#ifndef tmd
//    freopen("harbingers.in","r",stdin);
//    freopen("harbingers.out","w", stdout);
//#endif

    cin >> n;
    REP (i, n-1) {
        int u, w, d;
        cin >> u >> w >> d;
        edge[u].emplace_back(w, d);
        edge[w].emplace_back(u, d);
    }

    for (int i=2; i<=n; i++) {
        cin >> S[i] >> V[i];
    }

    root[0] = new Node(0, MOD);
    dfs(1, 0);
    for (int i=2; i<=n; i++) {
        cout << dp[i] << " \n"[i==n];
    }
}

// MLE
