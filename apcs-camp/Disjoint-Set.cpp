#include <iostream>
#include <vector>
using namespace std;

vector<int> parent, subtree_size;

void init (int n) {
  parent.resize(n);
  subtree_size.resize(n);
  for (int i=0; i<n; i++) {
    parent[i] = i; // 每個人都是自己當根的樹
    subtree_size[i] = 1; // 樹大小一開始是 1
  }
}

int getRoot (int x) { // 尋找 x 所屬的集合的樹根
  if (x == parent[x]) return x; // 已經是根
  else {
    int root = getRoot(parent[x]); // 遞迴求根
    parent[x] = root; // 路徑壓縮
    return root;
  }
}

bool mergeSet (int x, int y) { // 如果本來就是同集合回傳 false
  x = getRoot(x), y = getRoot(y);
  if (x == y) return false;

  // 確保 x 集合比較小 （啟發式合併）
  if (subtree_size[x] > subtree_size[y]) swap(x, y); 

  // 把 x 接向 y
  parent[x] = y;
  subtree_size[y] += subtree_size[x];
  return true;
}
