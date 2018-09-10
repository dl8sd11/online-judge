#include <bits/stdc++.h>
using namespace std;

int n,x,y;
int leaf_cnt;
int par[40];
int dep[40];
int val[40];
const int INF = 0x3f3f3f3f;
vector<int> e[40];

void dfs(int nd,bool mn_mx,int ub,int lb){
  int 
  int ret = (mn_mx?-INF:INF);
  cout<<"ND: "<<nd<<" EX[dep[nd]]: "<<ex[dep[nd]]<<endl;
  for(auto v:e[nd]){
    dfs(v,!mn_mx);
    if(mn_mx)ret = max(ret,val[v]);
    else ret = min(ret,val[v]);
  }
  if(e[nd].size())val[nd] = ret;

}
int main(){
  cin>>n;
  init();
  for(int i=1;i<n;i++){
    cin>>par[i];
    e[par[i]].push_back(i);
  }
  for(int i=0;i<n;i++){
    cin>>val[i];
  }

  dep[0] = -1;
  dfs(0,1,INF,-INF); // max
  for(int i=0;i<n;i++)cout<<dep[i]<<" ";
  cout<<endl;
  for(int i=0;i<n;i++)cout<<val[i]<<" ";
  cout<<endl;
  // cout<<val[0]<<endl;
}
