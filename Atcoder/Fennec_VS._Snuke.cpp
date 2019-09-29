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
const ll MOD = 1000000007;

int par[MAXN], n, dep[MAXN];
vector<int> edge[MAXN];

void build_par (int nd, int p) {
    par[nd] = p;
    dep[nd] = dep[p] + 1;
    for (auto v : edge[nd]) {
        if (v != p) {
            build_par(v, nd);
        }
    }
}

int wsz;
void dfs (int nd) {
    wsz++;
    debug(nd);
    for (auto v : edge[nd]) {
        if (v != par[nd]) {
            dfs(v);
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    build_par(1, 1);

    int wt = n;
    REP (i, (dep[n] - dep[1] - 1) / 2) {
        wt = par[wt];
    }
    debug(wt);
    dfs(wt);

    int bsz = n - wsz;

    debug(bsz, wsz);
    if (bsz <= wsz) {
        cout << "Snuke" << endl;
    } else {
        cout << "Fennec" << endl;
    }
    return 0;
}
