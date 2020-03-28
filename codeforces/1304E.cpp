#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXLG = __lg(MAXN) + 2;

int n, q;

int dep[MAXN], anc[MAXLG][MAXN];
vector<int> edge[MAXN];

void dfs (int nd, int par) {
    anc[0][nd] = par;
    dep[nd] = dep[par] + 1;
    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v, nd);
        }
    }
}

void build () {
    dfs(1, 0);
    for (int i=1; i<MAXLG; i++) {
        for (int j=1; j<=n; j++) {
            anc[i][j] = anc[i-1][anc[i-1][j]];
        }
    }
}

int dis (int x, int y) {
    int sdep = dep[x] + dep[y];

    if (dep[x] > dep[y]) {
        swap(x, y);
    }
    for (int i=MAXLG-1; i>=0; i--) {
        if (dep[anc[i][y]] >= dep[x]) {
            y = anc[i][y];
        }
    }
    if (x == y) {
        return sdep - dep[x]*2;
    }

    for (int i=MAXLG-1; i>=0; i--) {
        if (anc[i][x] != anc[i][y]) {
            x = anc[i][x];
            y = anc[i][y];
        }
    }

    assert(anc[0][x] == anc[0][y]);
    return sdep - dep[anc[0][x]]*2;
}

bool check (int dis, int target) {
    return dis <= target && !((dis^target)&1);
}

int main () {
    cin.tie(0);

    cin >> n;
    for (int i=0; i<n-1; i++) {
        int u, v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }
    build();

    cin >> q;
    while (q--) {
        int x, y, a, b, k;
        cin >> x >> y >> a >> b >> k;

        bool ans = false;

        ans |= check(dis(a,b), k);
        ans |= check(dis(a,x)+1+dis(y,b), k);
        ans |= check(dis(a,y)+1+dis(x,b), k);

        cout << (ans ? "YES" : "NO") << '\n';
    }
}
