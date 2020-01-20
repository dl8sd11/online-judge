#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
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


const int MAXN = 100005;
const int MAXLG = __lg(MAXN) + 2;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, q;
vector<int> edge[MAXN];
int anc[MAXLG][MAXN];
int dep[MAXN];

void dfs (int nd, int par) {
    anc[0][nd] = par;
    dep[nd] = dep[par] + 1;
    for (int v : edge[nd]) {
        if (v != par) {
            dfs(v, nd);
        }
    }
}

void build_anc () {
    dfs(1,1);
    for (int i=1;i<MAXLG;i++) {
        for (int j=1;j<=n;j++) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }
}

int lca (int u, int v) {
    if (dep[u] > dep[v]) {
        swap(u, v);
    }
    for (int i=MAXLG-1;i>=0;i--) {
        if (dep[anc[i][v]] >= dep[u]) {
            v = anc[i][v];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i=MAXLG-1;i>=0;i--) {
        if (anc[i][u] != anc[i][v]) {
            u = anc[i][u];
            v = anc[i][v];
        }
    }

    return anc[0][u];
}

int dis (int u, int v) {
    int ca = lca(u,v);
    return dep[u]+dep[v]-dep[ca]*2;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> q;
    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    build_anc();

    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;

        pair<int,int> res;
        for (int u : {a,b,c}) {
            for (int v : {a,b,c}) {
                if (u < v) {
                    int cp = lca(u, v);
                    res = max(res, {dep[cp],cp});
                }
            }
        }

        int sum = 0;
        for (auto v : {a,b,c}) {
            sum += dis(res.second, v);
        }

        cout << res.second << " " << sum << endl;
    }
}
