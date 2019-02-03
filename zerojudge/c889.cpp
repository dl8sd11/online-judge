#include <bits/stdc++.h>
using namespace std;

int n,m;
vector<int> edge[100004];
bool vis[100004];
bool color[100004];

pair<int,int> dfs(int nd,bool part) {
    vis[nd] = true;
    color[nd] = part;

    int x = 0,y = 0;
    for (int v : edge[nd]) {
        if (!vis[v]) {
            pair<int,int> son = dfs(v,!part);
            if (son.first == -1) {
                return {-1,-1};
            }
            x += son.first;
            y += son.second;
        } else {
            if (color[v] == part) {
                return {-1,-1};
            }
        }
    }
    if (part) {
        y++;
    } else{
        x++;
    }
    return {x,y};
}
/********** Good Luck :) **********/
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i=0;i<m;i++) {
        int u,v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    bool is_bipartite = true;
    int ans = 0;
    for (int i=1;i<=n;i++) {
        if (!vis[i]) {
            pair<int,int> ret = dfs(i,0);
            if (ret.first == -1) {
                is_bipartite = false;
                break;
            } else {
                ans += min(ret.first,ret.second);
            }
        }
    }

    if (is_bipartite) {
        cout << ans << endl;
    } else{
        cout << 0 << endl;
    }
    return 0;
}
