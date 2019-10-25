#include <bits/stdc++.h>
typedef long long ll;
#define SZ(i) int(i.size())
using namespace std;

const int MAXN = 200005;

int n;
vector<pair<int,int> > edge[MAXN];
ll sum[MAXN], ans;

void dfs_pre (int nd, int par) {
    for (auto v : edge[nd]) {
        if (v.first != par) {
            dfs_pre(v.first, nd);
            sum[nd] += min(sum[v.first], ll(v.second));
        }
    }
    if (nd != par && SZ(edge[nd]) == 1) {
        sum[nd] = 0x3f3f3f3f;
    }
}

void dfs_sol (int nd, int par, int tp) {
    if (SZ(edge[nd]) != 1 || nd == par) {
        ans = max(ans, sum[nd] + tp);
    }
    for (auto v : edge[nd]) {
        if (v.first != par) {
            ll tran = sum[nd] - min(sum[v.first], ll(v.second)) + tp;
            dfs_sol(v.first, nd, min(tran, ll(v.second)));
        }
    }
}

int main () {
    cin >> n;
    for (int i=0; i<n-1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edge[u].emplace_back(v, w);
        edge[v].emplace_back(u, w);
    }

    int root = 1;
    for (int i=1; i<=n; i++) {
        if (SZ(edge[i]) > 1) {
            root = i;
        }
    }

    dfs_pre(root, root);
    dfs_sol(root, root, 0);

    cout << ans << endl;
}
