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

const int MAXN = 50004;
const int MAXLG = __lg(MAXN) + 3;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, k;
int anc[MAXLG][MAXN], cnt[MAXN], ans, dep[MAXN];
vector<int> edge[MAXN];

void dfs_anc (int nd, int par) {
    anc[0][nd] = par;
    dep[nd] = dep[par] + 1;
    for (auto v : edge[nd]) {
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
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    for (int i=MAXLG-1;i>=0;i--) {
        if (dep[anc[i][u]] >= dep[v]) {
            u = anc[i][u];
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

void dfs_pre (int nd) {
    for (auto v : edge[nd]) {
        if (v != anc[0][nd]) {
            dfs_pre(v);
            cnt[nd] += cnt[v];
        }
    }
    ans = max(ans, cnt[nd]);
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    #ifndef tmd

    freopen("maxflow.out","w", stdout);
    freopen("maxflow.in","r", stdin);

    #endif // tmd

    cin >> n >> k;
    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    dfs_anc(1, 0);
    build_anc();

    REP (i, k) {
        int u, v;
        cin >> u >> v;
        cnt[u]++;
        cnt[v]++;

        int ca = lca(u,v);
        cnt[ca]--;
        cnt[anc[0][ca]]--;
    }

    dfs_pre(1);
    cout << ans << endl;
}
