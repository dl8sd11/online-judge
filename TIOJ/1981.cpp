#include <bits/stdc++.h>
using namespace std;
#define MEM(i,n) memset(i,n,sizeof(i));
#define REP(i,n) for(int i=0;i<n;i++)
#define pb push_back
int n,m,x,y;
const int MAXN =1000003;
vector<int> e[MAXN];
vector<int> et[MAXN];
vector<int> tod;
vector<int> se[MAXN];
int scc[MAXN];
int sz[MAXN];
int dp[MAXN];
bool visit[MAXN];
void DFS1(int idx){
  for(auto v:e[idx]){
    if(visit[v])continue;
    visit[v]=1;
    DFS1(v);
  }
  tod.pb(idx);
}
void DFS2(int idx,int c){
  scc[idx]=c;sz[c]++;
  for(auto v:et[idx]){
    if(visit[v])continue;
    visit[v]=1;
    DFS2(v,c);
  }
}
int solve(int idx){
  int ret = 0;
  for(auto v:se[idx]){
    if(dp[v]==-1)solve(v);
    ret=max(ret,dp[v]);
  }
  return dp[idx]=ret+sz[idx];
}
int main(){
  cin>>n>>m;
  REP(i,m)cin>>x>>y,e[x].pb(y),et[y].pb(x);
  REP(i,n) if(!visit[i])visit[i]=1,DFS1(i);
  reverse(tod.begin(),tod.end());
  MEM(visit,0);
  for(auto v:tod) if(!visit[v]) visit[v]=1,DFS2(v,v);
  REP(i,n)for(auto v:e[i])if(scc[i]!=scc[v])se[scc[i]].pb(scc[v]);
  int ans = -1;
  MEM(dp,-1);
  REP(i,n) {
    if(sz[i]){
      if(dp[i]==-1)solve(i);
      ans=max(ans,dp[i]);
    }
  }
  cout<<ans<<endl;
}
