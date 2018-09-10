#include <bits/stdc++.h>
using namespace std;

const int MAXN = 403;
int n,m,e,u,v;
vector<int> edge[MAXN];
bool vis[MAXN];
int yp[MAXN];

bool DFS(int x){


  for(auto i:edge[x]){
    assert(i<m&&i>=0);
    if(vis[i])continue;
    vis[i] = 1;
    if( yp[i]==-1 || DFS(yp[i]) ){
	yp[i] = x;
	return true;
     }
  }
return false;
}

int main(){
  cin>>n>>m>>e;
  for (int i=0;i<e;i++) {
    cin>>u>>v;
    u--,v--;
    edge[u].push_back(v);
  }


  memset(yp,-1,sizeof(int) * m);



  int c = 0;
  for (int i=0;i<n;i++) {
    memset(vis,0,sizeof(bool) *m);

    if(DFS(i))c++;
  }
  cout<<c<<endl;
}
