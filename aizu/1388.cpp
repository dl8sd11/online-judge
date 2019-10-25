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
const int MAXLG = __lg(MAXN) + 2;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;


typedef pair<int, int> pii;

int n, m, djs[MAXN];
vector<int> tree[MAXN];
vector<pii> n_tree;

set<int> virt_v;
vector<int> virt_e[MAXN];

int fnd (int x) {
    return djs[x] == x ? x : (djs[x] = fnd(djs[x]));
}

bool mrg (int x, int y) {
    debug(x, y);
    x = fnd(x), y = fnd(y);
    debug(x, y);
    if (x == y) {
        return false;
    }
    djs[x] = y;
    debug(djs[x], djs[y]);
    return true;
}

int anc[MAXLG][MAXN], dep[MAXN];
void dfs_anc (int nd, int par) {
    anc[0][nd] = par;
    dep[nd] = dep[par] + 1;
    for (auto v : tree[nd]) {
        if (v != par) {
            dfs_anc(v, nd);
        }
    }
}

void build_anc () {
    REP1 (i, MAXLG-1) {
        REP1 (j, n) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }
}

int lca (int u, int v) {
    if (dep[u] > dep[v]) {
        swap(u, v);
    }
    for (int i=MAXLG-1; i>=0; i--) {
        if (dep[anc[i][v]] >= dep[u]) {
            v = anc[i][v];
        }
    }
    if (u == v) {
        return u;
    }

    for (int i=MAXLG-1; i>=0; i--) {
        if (anc[i][v] != anc[i][u]) {
            v = anc[i][v];
            u = anc[i][u];
        }
    }
    return anc[0][v];
}

void build_virt (int nd, int par, int lst) {
    if (virt_v.count(nd)) {
        if (lst != -1) {
            virt_e[nd].emplace_back(lst);
            virt_e[lst].emplace_back(nd);
        }
        lst = nd;
    }
    for (auto v : tree[nd]) {
        if (v != par) {
            build_virt(v, nd, lst);
        }
    }
}

bool sub[102];

vector<pii> cycle_e;

bool xor_path (int nd, int par, int goal) {
    if (nd == goal) {
        return true;
    } else {
        for (auto v : virt_e[nd]) {
            if (v != par) {
                if (xor_path(v, nd, goal)) {
                    cycle_e.emplace_back(min(nd, v), max(nd, v));
                    debug(nd, v);
                    return true;
                }
            }
        }
    }
    return false;
}

int deg[MAXN];
void solve (int id, int &ans) {
    if (id == SZ(n_tree)) {
        cycle_e.clear();
        vector<int> curv;
        REP (i, SZ(n_tree)) {
            if (sub[i]) {
                curv.emplace_back(n_tree[i].first);
                curv.emplace_back(n_tree[i].second);
                debug(n_tree[i].first, n_tree[i].second);
                xor_path(n_tree[i].first, -1, n_tree[i].second);
            }
        }


        sort(cycle_e.begin(), cycle_e.end());
        REP (i, SZ(cycle_e)) {
            int x = i;
            while (i < SZ(cycle_e) &&cycle_e[i] == cycle_e[x]) {
                debug(cycle_e[i].first, cycle_e[i].second);
                i++;
            }
            if ((i-x) & 1) {
                deg[cycle_e[x].first]++;
                deg[cycle_e[x].second]++;
                curv.emplace_back(cycle_e[x].first);
                curv.emplace_back(cycle_e[x].second);
                mrg(cycle_e[x].first, cycle_e[x].second);
            }
            i--;
        }

        REP (i, SZ(n_tree)) {
            if (sub[i]) {
                deg[n_tree[i].first]++;
                deg[n_tree[i].second]++;
                mrg(n_tree[i].first, n_tree[i].second);
                debug(n_tree[i].first, n_tree[i].second);
                // debug(fnd(n_tree[i].first), fnd(n_tree[i].second));
#ifdef tmd
                REP1 (j, n) {
                    cout << djs[j] << " \n"[j==n];
                }
#endif
            }
        }

        sort(curv.begin(), curv.end());
        curv.resize(unique(curv.begin(), curv.end()) - curv.begin());
        if (curv.empty()) {
            return;
        }
        int hd = fnd(curv.front());
        bool flag = true;
        for (auto v : curv) {
            debug(v, fnd(v));
            if (fnd(v) != hd) {
                flag = false;
            }
            if (deg[v] != 2) {
                flag = false;
                debug(v, deg[v]);
            }
        }

        for (auto v : curv) {
            djs[v] = v;
            deg[v] = 0;
        }
        ans += flag;
        debug(flag);
    } else {
        sub[id] = true;
        solve(id+1, ans);
        sub[id] = false;
        solve(id+1, ans);
    }
}

void init_djs () {
    REP (i, MAXN) {
        djs[i] = i;
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    init_djs();
    cin >> n >> m;
    REP (i, m) {
        int u, v;
        cin >> u >> v;
        if (mrg(u, v)) {
            tree[u].emplace_back(v);
            tree[v].emplace_back(u);
        } else {
            n_tree.emplace_back(u, v);
        }
    }
    init_djs();
    debug(SZ(n_tree));

    dfs_anc(1, 1);
    build_anc();

    vector<int> vtmp;
    REP (i, SZ(n_tree)) {
        vtmp.emplace_back(n_tree[i].first);
        vtmp.emplace_back(n_tree[i].second);
    }

    REP (i, SZ(vtmp)) {
        virt_v.insert(vtmp[i]);
        REP (j, i) {
            virt_v.insert(lca(vtmp[i], vtmp[j]));
        }
    }

    build_virt(1, 1, -1);
    #ifdef tmd
        for (auto v : virt_v) {
            debug(v);
            for (auto t : virt_e[v]) {
                cout << t << " ";
            }
            cout << endl;
        }
    #endif


    int ans = 0;
    solve(0, ans);

    cout << ans << endl;
    return 0;
}

/*
13 15
1 2
2 3
3 4
4 5
3 7
7 6
7 8
2 10
10 9
10 11
1 13
13 12
5 6
8 9
10 13
*/
