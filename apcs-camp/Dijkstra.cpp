#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f;

// 求 s 到 t 最短路
int dijkstra (int s, int t, vector<vector<pair<int, int>>> edges) {
  int n = edges.size();
  vector<int> dis(n, INF), vis(n, 0);

  dis[s] = 0;
  priority_queue<pair<int, int>,vector<pair<int, int>>,greater<pair<int, int>>> pq;
  pq.emplace(0,s);

  while (!pq.empty()) {
    // 找 vis 是 false 最近的點
    int found = pq.top().second;
    pq.pop();

    // 如果 found 已經被搜尋過（過期）就跳過
    if(vis[found]) continue;
    vis[found]=1;

    for(pair<int, int> adj : edges[found]){
      int to = adj.first;
      int weight = adj.second;
      // 鬆弛
      if(dis[to] > dis[found] + weight){
        dis[to] = dis[found] + weight;
        pq.emplace(dis[to], to);
      }
    }
  }
}