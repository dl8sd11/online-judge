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

const int MAXN = 500005;
const ll MOD = 1000000007;

int n, k;
vector<pii> edges;
vector<int> G[MAXN], T[MAXN];

vector<int> tree, comp;

int s[MAXN], cnt[MAXN];
map<int,int> cur[MAXN];
set<int> open[MAXN];

void add (int f, int t) { //
    if (cur[f].size() > cur[t].size()) {
        swap(cur[f], cur[t]);
        swap(open[f], open[t]);
    }

    for (auto v : open[f]) {
        open[t].insert(v);
    }
    for (auto p : cur[f]) {
        cur[t][p.X] += p.Y;
        if (cur[t][p.X] == cnt[p.X]) {
            open[t].erase(p.X);
        }
    }

    open[f].clear();
    cur[f].clear();
}

void dfsEdg(int nd, int pa, int id) {

    cur[nd][s[nd]]++;
    if (cnt[s[nd]] != 1) {
        open[nd].insert(s[nd]);
    }

    for (auto eid : G[nd]) {
        int v = edges[eid].X ^ edges[eid].Y ^ nd;
        if (v != pa) {
            dfsEdg(v, nd, eid);
            add(v, nd);
        }
    }

    if (id == -1) {
        return;
    }

    if (open[nd].empty()) {
        tree.eb(id);
    } else {
        comp.eb(id);
    }
}

int djs[MAXN];

int fnd (int nd) {
    return nd == djs[nd] ? djs[nd] : djs[nd] = fnd(djs[nd]);
}

void mrg (int x, int y) {
    x = fnd(x);
    y = fnd(y);
    djs[x] = y;
}

int deg[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;
    REP (i, n-1) {
        int u,v;
        cin >> u >> v;
        edges.eb(u, v);
        G[u].eb(i);
        G[v].eb(i);
    }

    REP1 (i, n) {
        cin >> s[i];
        cnt[s[i]]++;
    }


    dfsEdg(1, 1, -1);

    for (int i=1; i<=n; i++) {
        djs[i] = i;
    }

    for (auto id : comp) {
        mrg(edges[id].X, edges[id].Y);
    }
    vector<int> nodes;
    for (int i=1; i<=n; i++) {
        if (fnd(i) == i) {
            nodes.eb(i);
        }
    }

    debug(tree, comp, nodes);
    for (auto id : tree) {
        int u, v;
        tie(u, v) = edges[id];

        deg[fnd(u)]++;
        deg[fnd(v)]++;
    }

    int ans = 0;
    for (auto v : nodes) {
        ans += (deg[v] == 1);
    }

    if (ans == 1) {
        cout << 0 << endl;
    } else {
        cout << (ans+1)/2 << endl;
    }
}
