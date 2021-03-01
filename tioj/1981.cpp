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
vector<int> tod2;
int d[MAXN];
vector<int> se[MAXN];
int scc[MAXN];
int sz[MAXN];
int dp[MAXN];
bool visit[MAXN];
bool visit2[MAXN];
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
    if(visit2[v])continue;
    visit2[v]=1;
    DFS2(v,c);
  }
}

int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  cin>>n>>m;
  REP(i,m)cin>>x>>y,e[x].pb(y),et[y].pb(x);
  REP(i,n) if(!visit[i])visit[i]=1,DFS1(i);
  for(int i=tod.size()-1;i>=0;i--) if(!visit2[tod[i]]) visit2[tod[i]]=1,DFS2(tod[i],tod[i]);
  REP(i,n)for(auto v:e[i])if(scc[i]!=scc[v])se[scc[i]].pb(scc[v]),d[scc[v]]++;
  int ans = -1;
  stack<int,vector<int>> q;
  REP(i,n)if(sz[i])if(!d[i])q.push(i);
  while(q.size()){
    int now = q.top();q.pop();
    tod2.pb(now);
    for(auto v:se[now])if(--d[v]==0)q.push(v);
  }
  for(int i=tod2.size()-1;i>=0;i--){
    int ret = 0;
    for(auto v:se[tod2[i]])ret=max(ret,dp[v]);
    ans=max(ans,dp[tod2[i]]=ret+sz[tod2[i]]);
  }
  cout<<ans<<endl;
}
