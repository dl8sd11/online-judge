#include <bits/stdc++.h>
using namespace std;
const int MAXN = 300002;
int n,a[MAXN],ans,r[MAXN],b[MAXN],rc,bc;

vector<int> edge[MAXN];
void dfs(int nd,int par) {
    for (int v : edge[nd]) {
        if (v != par) {
            dfs(v,nd);
            r[nd] += r[v];
            b[nd] += b[v];
        }
    }
    if ((r[nd] == rc && b[nd] == 0) || (r[nd] == 0 && b[nd] == bc)) {
        ans++;
    }
}
int main () {
    cin >> n;
    for (int i=1;i<=n;i++) {
        cin >> a[i];
        if (a[i] == 1) {
            r[i]++;
            rc++;
        } else if (a[i] == 2) {
            b[i]++;
            bc++;
        }
    }

    for (int i=0;i<n-1;i++) {
        int u,v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    dfs(1,1);
    cout << ans << endl;
}