#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

struct Edge {
  int to, from, wei;
};

void BellmanFord (int n, int s, vector<Edge> edges) {
  vector<int> dis(n, INF);
  dis[s] = 0;

  // 如果沒負環 v-1 輪找到大家最短距離
  for (int i=0; i<n-1; i++) { 
      for (auto adj : edges) {
          // 鬆弛
          if (dis[adj.to] > dis[adj.from] + adj.wei) {
              dis[adj.to] = dis[adj.from] + adj.wei;
          }
      }
  }
}