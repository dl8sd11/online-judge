#include <bits/stdc++.h>
using namespace std;

vector<int> bfs (int n, int s, vector<vector<int> > edges) {
  queue<int> bfs_queue;
  vector<int> dis(n, -1); // 距離預設 -1
  bfs_queue.emplace(s); // 推入起點
  dis[s] = 0;

  while (!bfs_queue.empty()) {
      int current = bfs_queue.front();
      bfs_queue.pop();

      for (int adj : edges[current]) { // 鄰邊
          if (dis[adj] == -1) { // 如果沒有被探索過
              dis[adj] = dis[current] + 1;
              bfs_queue.emplace(adj);
          }
      }
  }
}