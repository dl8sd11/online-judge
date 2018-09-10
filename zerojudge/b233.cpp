#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define pb push_back
#define ALL(i) i.begin(),i.end()
#define MEM(i,n) memset(i,n,sizeof(n));
const int MAXN = (ll)3e4 + 5;
int n,m,k,x,y;
vector<int> e[MAXN];
vector<int> av;
int sz[MAXN],low[MAXN],h[MAXN],w[MAXN];
void DFS(int idx,int par){
  sz[idx]=1;
  low[idx]=h[idx]=h[par]+1;
  bool isav = 1;
  for(auto v:e[idx]){
    if(v==par)continue;
    if(sz[v]){
      low[idx]=min(low[idx],h[v]);
    }else{
      DFS(v,idx);
      sz[idx]+=sz[v];
      if(low[v]>=h[idx]) {
        isav = 1;
        w[idx]+=sz[v];
      }
      low[idx]=min(low[idx],low[v]);
    }
  }
  if(isav&&idx!=k)av.pb(idx);
}
int main(){
  cin>>n>>m;
  REP(i,m)cin>>x>>y,e[x].pb(y),e[y].pb(x);
  cin>>k;
  DFS(k,k);
  int ans = 1000000;
  int id = 1000000;

  for(auto v:av){
    if(sz[k]-w[v]<ans&&w[v]>0)ans=sz[k]-w[v],id=v;
    else if(sz[k]-w[v]==ans&&w[v]>0&&v<id)id=v;
  }
  if(id==1000000)cout<<0<<endl;
  else cout<<id<<' '<<ans<<endl;
}
