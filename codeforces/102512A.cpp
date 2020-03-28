#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
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

const int MAXN = 200005;
const int MAXLG = __lg(MAXN) + 3;
const ll MOD = 1000000007;


int n, m;
vector<int> graph[MAXN], tree[MAXN*2];

int low[MAXN], dfn[MAXN], dfs_clock = 0;
vector<vector<int> > bcc;
bool is_cut[MAXN];

vector<int> stk;
void dfs_bcc (int nd, int pa) {
    low[nd] = dfn[nd] = dfs_clock++;
    stk.eb(nd);
    debug(nd, pa);
    for (auto v : graph[nd]) {
        if (v != pa) {
            if (dfn[v] == -1) { // tree edge
                dfs_bcc(v, nd);
                low[nd] = min(low[nd], low[v]);
                if (low[v] >= dfn[nd]) {
                    debug(nd, pa, v, low[v], dfn[nd]);
                    is_cut[nd] |= (dfn[nd] > 0 || dfn[v] > 1); // not root or > 1 child
                    vector<int> new_comp = {nd};
                    while (new_comp.back() != v) {
                        new_comp.eb(stk.back());
                        stk.pop_back();
                    }
                    bcc.eb(new_comp);
                }
            } else { // back edge
                low[nd] = min(low[nd], dfn[v]);
            }


        }
    }
}

int tree_id[MAXN], tree_sz;
void build_block_cut_tree () {
    REP1 (i, n) {
        if (is_cut[i]) {
            tree_id[i] = tree_sz++;
        }
    }
    for (auto comp : bcc) {
        for (auto v : comp) {
            if (is_cut[v]) {
                tree[tree_id[v]].eb(tree_sz);
                tree[tree_sz].eb(tree_id[v]);
            } else {
                tree_id[v] = tree_sz;
            }
        }
        tree_sz++;
    }
    pary(is_cut+1, is_cut+n+1);
}

int anc[MAXLG][MAXN*2], dep[MAXN*2];
void dfs_anc (int nd, int pa) {
    dep[nd] = dep[pa] + 1;
    anc[0][nd] = pa;

    for (auto v : tree[nd]) {
        if (v != pa) {
            dfs_anc(v, nd);
        }
    }
}

void build_anc () {
    for (int i=1; i<MAXLG; i++) {
        for (int j=0; j<tree_sz; j++) {
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
            u = anc[i][u];
            v = anc[i][v];
        }
    }
    return anc[0][u];
}
/*
o-x-o-x-o-x-o
*/
int dist (int u, int v) {
    int ca = lca(u, v);
    debug(u, v, ca);
    return dep[u] + dep[v] - 2*dep[ca];
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].eb(v);
        graph[v].eb(u);
    }

    memset(dfn, -1, sizeof(dfn));
    debug(dfs_clock);
    dfs_bcc (1, 0);
    debug(bcc);
    build_block_cut_tree();
    dfs_anc(0, 0);
    build_anc();

    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        int len = 0;
        if (is_cut[u]) {
            len--;
        }
        if (is_cut[v]) {
            len--;
        }

        u = tree_id[u];
        v = tree_id[v];
        len += dist(u, v);

        if (u == v) {
            cout << 0 << endl;
            continue;
        }


        debug(len);
        cout << len / 2 << endl;
    }
}

/*
9 14
1 2
1 3
3 4
3 5
4 5
4 7
5 6
5 7
6 7
1 8
1 9
2 9
2 8
9 8
1
4 9

*/
