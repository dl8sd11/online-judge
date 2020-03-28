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
const ll MOD = 1000000007;
const int INF = 0x3f3f3f3f;

int n, m, q, w[MAXN];
vector<int> graph[MAXN], tree[MAXN];
int bid[MAXN], bsz;

int low[MAXN], dfn[MAXN], dfs_clock;
bool is_cut[MAXN];
bool id_cut[MAXN];

vector<int> stk;
vector<vector<int> > bcc;

void dfs_bcc(int nd, int pa) {
    low[nd] = dfn[nd] = ++dfs_clock;
    stk.eb(nd);

    for (auto v : graph[nd]) {
        if (v != pa) {
            if (dfn[v]) {
                low[nd] = min(low[nd], dfn[v]);
            } else {
                dfs_bcc(v, nd);
                low[nd] = min(low[nd], low[v]);
                if (low[v] >= dfn[nd]) {
                    is_cut[nd] |= (dfn[nd] > 1 || dfn[v] > 2);
                    vector<int> comp = {nd};
                    while (comp.back() != v) {
                        comp.eb(stk.back());
                        stk.pop_back();
                    }
                    bcc.eb(comp);
                }
            }
        }
    }
}

void build_block_cut_tree() {
    debug(bcc);
    REP1 (i, n) {
        if (is_cut[i]) {
            debug(i);
            id_cut[bsz] = true;
            bid[i] = bsz++;
        }
    }
    for (auto comp : bcc) {
        for (auto v : comp) {
            if (is_cut[v]) {
                tree[bid[v]].eb(bsz);
                tree[bsz].eb(bid[v]);
                debug(bsz, bid[v]);
            } else {
                bid[v] = bsz;
            }
        }
        bsz++;
    }
}

int sz[MAXN], hd[MAXN], par[MAXN], in[MAXN], dep[MAXN];
void dfs_sz(int nd, int pa) {
    sz[nd] = 1;
    for (int &v : tree[nd]) {
        if (v != pa) {
            dfs_sz(v, nd);
            sz[nd] += sz[v];
            if (tree[nd][0] == pa || sz[v] >= sz[tree[nd][0]]) {
                swap(tree[nd][0], v);
            }
        }
    }
}

int hd_clock;
void dfs_hd (int nd, int pa) {
    par[nd] = pa;
    in[nd] = hd_clock++;
    dep[nd] = dep[pa] + 1;

    for (int v : tree[nd]) {
        if (v != pa) {
            hd[v] = (v == tree[nd][0]) ? hd[nd] : v;
            dfs_hd(v, nd);
        }
    }
}

int seg[MAXN*4];
void buildSeg () {
    memset(seg, 0x3f, sizeof(seg));
}

int segQ (int l, int r) {
    int ret = INF;
    debug(l, r);
    for (l+=bsz, r+=bsz; l<r; l>>=1, r>>=1) {
        if (l&1) {
            ret = min(ret, seg[l++]);
        }
        if (r&1) {
            ret = min(ret, seg[--r]);
        }
    }
    debug(ret);
    return ret;
}

void segM (int x, int v) {
    debug(x, v);
    for (seg[x+=bsz]=v; x>1; x>>=1) {
        seg[x>>1] = min(seg[x], seg[x^1]);
    }
}

typedef priority_queue<pii,vector<pii>,greater<pii> > pqii;
pqii bmn[MAXN];

int pqMin (pqii &pq) {
    while (pq.size()) {
        const pii &tp = pq.top();
        if (w[tp.Y] != tp.X) {
            pq.pop();
        } else {
            break;
        }
    }
    return pq.empty() ? INF : pq.top().X;
}

void nodeUpd (int nd) {
    segM(in[nd], pqMin(bmn[nd]));
    if (id_cut[nd]) {
        segM(in[par[nd]], pqMin(bmn[par[nd]]));
    }
}

int pathQry (int u, int v) {
    int res = INF;
    debug(u, v, hd[u], hd[v]);
    while (hd[u] != hd[v]) {
        debug(u, v, hd[u], hd[v]);
        if (dep[hd[u]] > dep[hd[v]]) {
            swap(u, v);
        }
        res = min(res, segQ(in[hd[v]], in[v]+1));
        v = par[hd[v]];
    }
    if (dep[u] > dep[v]) {
        swap(u, v);
    }
    if (!id_cut[u]) {
        res = min(res, pqMin(bmn[par[u]]));
    }
    debug(u, v);
    return min(res, segQ(in[u], in[v]+1));
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m >> q;
    REP1 (i, n) {
        cin >> w[i];
    }
    REP (i, m) {
        int u, v;
        cin >> u >> v;
        graph[u].eb(v);
        graph[v].eb(u);
    }

    dfs_bcc(1, 0);
    build_block_cut_tree();

    dfs_sz(0, 0);
    dfs_hd(0, 0);
    pary(in, in+bsz);
    pary(hd, hd+bsz);

    REP1 (i, n) {
        bmn[bid[i]].emplace(w[i], i);
        if (is_cut[i]) {
            bmn[par[bid[i]]].emplace(w[i], i);
        }
    }

    buildSeg();
    REP (i, bsz) {
        nodeUpd(i);
    }

    while (q--) {
        int x, y;
        char cmd;
        cin >> cmd >> x >> y;
        if (cmd == 'C') {
            w[x] = y;
            bmn[bid[x]].emplace(w[x], x);
            if (is_cut[x]) {
                bmn[par[bid[x]]].emplace(w[x], x);
            }
            nodeUpd(bid[x]);
        } else {

            cout << (x == y ? w[x] : pathQry(bid[x], bid[y])) << endl;
        }
    }
}
/*

5 5 1
4
3
1
4
3
2 1
3 1
4 3
5 1
2 3
A 2 5

5 5 10
2
3
1
1
1
2 1
3 1
4 3
5 1
2 3
A 2 4
A 1 1
C 1 4
A 2 4
C 5 3
C 4 4
A 2 5
A 5 1
A 5 3
C 1 2
*/
