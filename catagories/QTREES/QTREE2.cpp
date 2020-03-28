#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
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

const int MAXN = 10005;
const int MAXLG = __lg(MAXN) + 2;
const ll MOD = 1000000007;

int t;
int n;
vector<pii> edge[MAXN];
int ndep[MAXN], ddep[MAXN], anc[MAXLG][MAXN];

void dfs (int nd, int par) {
    ndep[nd] = ndep[par] + 1;
    anc[0][nd] = par;
    for (auto e : edge[nd]) {
        if (e.X != par) {
            ddep[e.X] = ddep[nd] + e.Y;
            dfs(e.X, nd);
        }
    }
}

void buildANC () {
    for (int i=1; i<MAXLG; i++) {
        for (int j=1; j<=n; j++) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }
}

int lca (int u, int v) {
    if (ndep[u] > ndep[v]) {
        swap(u, v);
    }
    for (int i=MAXLG-1; i>=0; i--) {
        if (ndep[anc[i][v]] >= ndep[u]) {
            v = anc[i][v];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i=MAXLG-1; i>=0; i--) {
        if (anc[i][u] != anc[i][v]) {
            u = anc[i][u];
            v = anc[i][v];
        }
    }
    return anc[0][u];
}

int kth (int v, int k) {
    for (int i=MAXLG-1; i>=0; i--) {
        if ((k>>i) & 1) {
            v = anc[i][v];
        }
    }
    return v;
}
/*********************GoodLuck***********************/
signed main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> n;
        for (int i=0; i<n-1; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            edge[u].eb(v, w);
            edge[v].eb(u, w);
        }

        dfs(1, 0);
        buildANC();

        string cmd;
        while (cin >> cmd) {
            if (cmd[1] == 'O') {
                for (int i=1; i<=n; i++) {
                    edge[i].clear();
                }
                break;
            } else if (cmd[1] == 'I') {
                int u, v;
                cin >> u >> v;
                int ca = lca(u, v);
                cout << ddep[u] + ddep[v] - 2*ddep[ca] << endl;
            } else {
                int u, v, k;
                cin >> u >> v >> k;
                int ca = lca(u, v);
                if (ndep[u] - ndep[ca] + 1 >= k) {
                    cout << kth(u, k-1) << endl;
                } else {
                    int sum = ndep[u] + ndep[v] - 2*ndep[ca];
                    cout << kth(v, sum-k+1) << endl;
                }
            }
        }

        cout << endl;
    }
}
