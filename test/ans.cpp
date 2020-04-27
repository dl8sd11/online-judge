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

const int MAXN = 1000006;
const ll MOD = 1000000007;

vector<pair<int,int> > G[MAXN];

int n, q;
int a[MAXN], b[MAXN];
int sum[MAXN], wu[MAXN];

vector<pair<int,int> > cases;

const int MAXLG = __lg(MAXN) + 2;
int anc[MAXLG][MAXN];
int dep[MAXN];

void dfs (int nd, int par) {
    sum[nd]  = a[nd] - b[nd];
    dep[nd] = dep[par] + 1;
    anc[0][nd] = par;
    for (auto v : G[nd]) {
        if (v.X != par) {
            dfs(v.X, nd);
            sum[nd] += sum[v.X];
            wu[v.X] = v.Y;
        }
    }

}


void build_anc () {
    for (int i=1;i<MAXLG; i++) {
        for (int j=1; j<=n; j++) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }
}

int lca (int u, int v) {
    if (dep[u] > dep[v]) {
        swap(u,v);
    }
    for (int i=MAXLG-1; i>=0; i--) {
        if (dep[anc[i][v]] >= dep[u]) {
            v = anc[i][v];
        }
    }
    if (v == u) {
        return u;
    }
    for (int i=MAXLG-1;i>=0; i--) {
        if (anc[i][v] != anc[i][u]) {
            v = anc[i][v];
            u = anc[i][u];
        }
    }
    return anc[0][u];
}
ll save (int cap) {
    // worst case: min
    
    ll worst = 1e18;
    for (auto p : cases) {
        int ca = lca(p.X, p.Y);

        int u, v;
        tie(u,v) = p;

        ll tot = 0;
        while (dep[u] > dep[ca]) {
            ll del = abs(sum[u]) - abs(sum[u]+cap);
            tot += del * wu[u];
            u = anc[0][u];
        }
        while (dep[v] > dep[ca]) {
            ll del = abs(sum[v]) - abs(sum[v]-cap);
            tot += del * wu[v];
            v = anc[0][v];
        }

        ll ioi = 0;
        tie(u, v) = p;
        while (dep[u] > dep[ca]) {
            ll del = abs(sum[u]) - abs(sum[u]-cap);
            ioi += del * wu[u];
            u = anc[0][u];
        }
        while (dep[v] > dep[ca]) {
            ll del = abs(sum[v]) - abs(sum[v]+cap);
            ioi += del * wu[v];
            v = anc[0][v];
        }

        worst = min(worst, max(ioi, tot));
    }


    return worst;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> q;

    for (int i=0;i<n-1;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u > v) {
            swap(u, v);
        }

        G[u].eb(v, w);
        G[v].eb(u, w);

    }
    for (int i=1; i<=n; i++) {
        cin >> a[i] >> b[i];
    }
    dfs(1, 0);
    build_anc();


    while (q--) {
        int u, v;
        cin >> u >> v;
        if (u > v) {
            swap(u, v);
        }
        cases.eb(u, v);
    }


    int L = 0, R = MOD;

    while (L < R - 10) {
        int len = (R - L) / 3;
        int M1 = L + len;
        int M2 = L + 2 * len;

        ll s1 = save(M1);
        ll s2 = save(M2);
        if (s1 == s2) {
            L = M1;
            R = M2;
        } else if (s1 > s2) {
            R = M2;
        } else {
            L = M1;
        }
    }


    ll mx = save(L);
    ll bst = L;
    debug(L, R);

    for (int i=L; i<=R; i++) {
        ll res = save(i);
        debug(i, res);
        if (res > mx) {
            bst = i;
            mx = res;
        }
    }

    cout << bst << " " << mx << endl;
}


