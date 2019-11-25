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
const int MAXLG = __lg(MAXN) + 3;
const ll MOD = 1000000007;

typedef pair<int,int> pii;

int n, ans[MAXN], anc[MAXLG][MAXN];
vector<int> edge[MAXN];
vector<pii> qry[MAXN];
vector<int> root;

void build_anc () {
    REP1 (i, MAXLG-1) {
        REP1 (j, n) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }
}

int kth_anc (int nd, int lev) {
    for (int i=MAXLG-1; i>=0; i--) {
        if (lev & (1<<i)) {
            nd = anc[i][nd];
        }
    }
    return nd;
}

int sz[MAXN], dep[MAXN], son[MAXN];

void makeInfo (int nd) {
    sz[nd] = 1;
    dep[nd] = dep[anc[0][nd]] + 1;
    for (auto v : edge[nd]) {
        makeInfo(v);
        sz[nd] += sz[v];
        if (sz[v] > sz[son[nd]]) {
            son[nd] = v;
        }
    }
}

int cnt[MAXN];
bool big[MAXN];
void addTree (int nd, int val) {
    cnt[dep[nd]] += val;
    for (auto v : edge[nd]) {
        if (!big[v]) {
            addTree(v, val);
        }
    }
}

void solve (int nd, bool keep) {
    debug(nd, keep, son[nd]);
    for (auto v : edge[nd]) {
        if (v != son[nd]) {
            solve(v, 0);
        }
    }
    if (son[nd] != 0) {
        solve(son[nd], 1);
        big[son[nd]] = true;
    }
    addTree(nd, 1);

    for (auto p : qry[nd]) {
        ans[p.second] = cnt[dep[nd]+p.first] - 1;
    }

    big[son[nd]] = false;
    if (!keep) {
        addTree(nd, -1);
    }
}

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP1 (i, n) {
        cin >> anc[0][i];
        edge[anc[0][i]].emplace_back(i);
        if (anc[0][i] == 0) {
            root.emplace_back(i);
        }
    }

    build_anc();
    int m;
    cin >> m;

    REP (i, m) {
        int v, p;
        cin >> v >> p;
        int kanc = kth_anc(v, p);
        debug(v, p, kanc);
        if (kanc != 0) {
            qry[kanc].emplace_back(p, i);
        }
    }

    for (auto r : root) {
        makeInfo(r);
        solve(r, 0);
    }

    REP (i, m) {
        cout << ans[i] << " \n"[i==m-1];
    }
}
/*
6
0 1 1 0 4 4
7
1 1
1 2
2 1
2 2
4 1
5 1
6 1

*/
