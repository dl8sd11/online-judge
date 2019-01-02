#include <bits/stdc++.h>
using namespace std;

int n,m,g[10][10];
bool vis[103];
int yp[103];
vector<int> edge[103];
int cti(int cx,int cy){
  return (cx*m + cy)/2;
}

bool DFS(int px){
  for(auto v:edge[px]){
    if(!vis[v]){
      vis[v] = 1;
      if(yp[v]==-1||DFS(yp[v])){
        yp[v] = px;
        return true;
      }
    }
  }
  return false;
}
int main() {
  cin>>n>>m;
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      cin>>g[i][j];
    }
  }

  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      if((i+j)&1)continue;
      if(i!=0&&g[i][j] == g[i-1][j])edge[cti(i,j)].emplace_back(cti(i-1,j));
      if(i!=n-1&&g[i][j] == g[i+1][j])edge[cti(i,j)].emplace_back(cti(i+1,j));
      if(j!=0&&g[i][j] == g[i][j-1])edge[cti(i,j)].emplace_back(cti(i,j-1));
      if(j!=m-1&&g[i][j] == g[i][j+1])edge[cti(i,j)].emplace_back(cti(i,j+1));
    }
  }

  int cnt = 0;
  memset(yp,-1,sizeof yp);
  for(int i=0;i<103;i++){
    memset(vis,0,sizeof vis);
    if(DFS(i))cnt++;
  }
  cout<<cnt<<endl;
}
