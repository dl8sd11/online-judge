#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000000;
vector<int> edge[MAXN];
int n,e,a,b,cnt,ti;
vector<int> st;
int low[MAXN],dfn[MAXN];
void DFS(int nd,int par){

  dfn[nd] = ++ti;
  if(low[nd])low[nd] = min(low[nd],dfn[nd]);
  else low[nd] = dfn[nd];
  st.push_back(nd);


  int prev = -1;

  for(int i=0;i<int(edge[nd].size());i++){
    int v = edge[nd][i];
    if(v==par&&v==prev){
      low[nd] = min(low[nd],low[v]);
    }
    prev = v;
    if(v==par)continue;
    
    

    if(!dfn[v]){
      DFS(v,nd);
    }
    low[nd] = min(low[nd],low[v]);

  }


  if(dfn[nd] == low[nd]){
    int j;
    cnt++;
    do{
      j = st.back();st.pop_back();
    }while(nd!=j);
  }

  
}

int main(){
  cin>>n>>e;
  for(int i=0;i<e;i++){
    cin>>a>>b;
    edge[a].push_back(b);
    edge[b].push_back(a);
  }

  for(int i=1;i<=n;i++)sort(edge[i].begin(),edge[i].end());
  
  for(int i=1;i<=n;i++){

    if(!dfn[i])DFS(i,i);
  }


  cout<<cnt<<endl;
}
