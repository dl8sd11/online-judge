#include <bits/stdc++.h>
using namespace std;
const int MAXN = 15003;
const int MAXLG = __lg(MAXN) + 2;
int anc[MAXLG][MAXN];
int dep[MAXN];
vector<int> edge[MAXN];
int n,q,a,b; 
void dfs(int nd,int par){
  anc[0][nd] = par;
  dep[nd] = dep[par] + 1;
  for(int v:edge[nd]){
    if(v!=par) dfs(v,nd);
  }
}
void build_lca(){
  for(int i=1;i<MAXLG;i++){
    for(int j=0;j<n;j++){
      anc[i][j] = anc[i-1][anc[i-1][j]];
    }
  }
}

int query(int u,int v){
  if(dep[u] < dep[v])swap(u,v);
  for(int i=MAXLG-1;i>=0;i--){
    if(dep[anc[i][u]] >= dep[v]) u = anc[i][u];
  }
  if(u==v)return u;

  for(int i=MAXLG-1;i>=0;i--){
    if(anc[i][u] != anc[i][v]) {
      u = anc[i][u];
      v = anc[i][v];
    }
  }

  return anc[0][u];
}
int main(){
  cin>>n>>q;
  for(int i=0;i<n-1;i++) cin>>a>>b,edge[a].emplace_back(b),edge[b].emplace_back(a);
  
  dfs(0,0);
  build_lca();
  for(int i=0;i<q;i++){
    cin>>a>>b;
    cout<<query(a,b)<<endl;
  }
}


// Doubling LCA
