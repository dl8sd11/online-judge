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

const int MAXN = 300005;
const ll MOD = 1000000007;

int n, k;
map<pair<int,int>, int> lst;
vector<int> qtid;

typedef pair<int,int> pii;

struct LOG {
    int u, v, su, sv;
};
vector<LOG> logs;

int djs[MAXN], sz[MAXN], comp, ans[MAXN];
int fnd (int x) {
    return djs[x] == x ? x : djs[x] = fnd(djs[x]);
}

void uni (int x, int y) {
    x = fnd(x);
    y = fnd(y);
    logs.push_back({x, y, sz[x], sz[y]});
    if (x == y) {
        return;
    }
    comp--;
    if (sz[x] > sz[y]) {
        swap(x, y);
    }
    djs[x] = y;
    sz[y] += sz[x];
}

void undo () {
    // assert(!logs.empty());
    LOG cur = logs.back();
    logs.pop_back();
    if (cur.u != cur.v) {
        comp++;
    }
    djs[cur.u] = cur.u;
    sz[cur.u] = cur.su;
    djs[cur.v] = cur.v;
    sz[cur.v] = cur.sv;
}

vector<pii> seg[MAXN*4];

void add_query (pii q, int qL, int qR, int v=1, int nL=0, int nR=k) {
    if (qL >= nR || qR <= nL || qL >= qR) {
        return;
    } else if (qL <= nL && nR <= qR) {
        seg[v].emplace_back(q);
    } else {
        int nM = (nL + nR) >> 1;
        add_query(q, qL, qR, v<<1, nL, nM);
        add_query(q, qL, qR, v<<1|1, nM, nR);
    }
}

void time_dfs (int v, int l, int r) {
    for (auto p : seg[v]) {
        uni(p.first, p.second);
    }
    if (l >= r - 1) {
        ans[l] = comp;
    } else {
        int m = (l + r) >> 1;
        time_dfs(v<<1, l, m);
        time_dfs(v<<1|1, m, r);
    }

    REP (i, SZ(seg[v])) {
        undo();
    }
}
/*********************GoodLuck***********************/
int main () {
#ifdef tmd
    IOS();
#else
    freopen("connect.in", "r", stdin);
    freopen("connect.out", "w", stdout);
#endif

    cin >> n >> k;

    comp = n;
    REP1 (i, n) {
        djs[i] = i;
        sz[i] = 1;
    }
    REP (i, k) {
        char cmd;
        cin >> cmd;
        if (cmd != '?') {
            int u, v;
            cin >> u >> v;
            // assert(u != v);
            if (u > v) {
                swap(u, v);
            }
            if (cmd == '+') {
                // assert(lst.count({u, v}) == 0);
                lst[{u, v}] = i;
            } else {
                // assert(lst.count({u, v}) == 1);
                add_query({u, v}, lst[{u, v}], i);
                lst.erase({u, v});
            }
        } else {
            qtid.emplace_back(i);
        }
    }

    for (auto edg : lst) {
        add_query({edg.first.first, edg.first.second}, edg.second, k);
    }

    time_dfs(1, 0, k);
    for (auto t : qtid) {
        cout << ans[t] << endl;
    }
    return 0;
}
