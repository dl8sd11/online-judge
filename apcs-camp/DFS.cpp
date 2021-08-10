#include <bits/stdc++.h>
using namespace std;

void dfs (int current, vector<bool> &vis, vector<vector<int>> edges) {
    vis[current] = true;
    for (int adj : edges[current]) {
        if (!vis[adj]) dfs(adj, vis, edges);
    }
}