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

const int MAXN = 3003;
const ll MOD = 1000000007;

struct Path {
    int pu, pv;
    ll s;
} path[MAXN][MAXN];

int n;
vector<int> edge[MAXN];
vector<pair<int,int> > plen[MAXN];

void dfs (int rt, int prt, int lst, int nd, int len) {
    path[rt][nd] = {prt, lst, -1};
    plen[len].eb(rt, nd);
    for (auto v : edge[nd]) {
        if (v != lst) {
            dfs(rt, prt, nd, v, len+1);
        }
    }
}

void build (int nd) {
    for (auto v : edge[nd]) {
        dfs(nd, v, nd, v, 1);
    }

}

int sz[MAXN], fa[MAXN];
void build_sz (int nd, int par) {
    sz[nd] = 1;
    fa[nd] = par;
    for (auto v : edge[nd]) {
        if (v != par) {
            build_sz(v, nd);
            sz[nd] += sz[v];
        }
    }
}

int get_sz (int nd, int par) {
    return fa[nd] == par ? sz[nd] : n - sz[par];
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    for (int i=0; i<n-1; i++) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    build_sz(1, 0);
    for (int i=1; i<=n; i++) {
        build(i);
    }

    ll bst = 0;
    for (int i=1; i<=n; i++) {
        for (auto p : plen[i]) { // u,v
            int u, v;
            tie(u, v) = p;
            int pu = path[u][v].pu;
            int pv = path[u][v].pv;

            int cur = get_sz(u, pu) * get_sz(v, pv);

            if (i == 1) {
                path[u][v].s = cur;
            } else {
                path[u][v].s = max(path[u][pv].s, path[pu][v].s) + cur;
            }

            bst = max(bst, path[u][v].s);
        }
    }

    cout << bst << endl;

}

