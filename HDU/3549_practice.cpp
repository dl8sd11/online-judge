#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back()
#define SZ(i) ll(i.size())
const ll MAXN = 100;
struct edge{ll u,ll v,ll cap,ll flow;}
vector<edge> edges;
vector<ll> G[MAXN];
bool vis[MAXN];
ll d[MAXN];
ll s,v;
void addEdge(ll u,ll v,ll cap){
  edges.pb((edge){u,v,cap,0});
  G[u].pb(SZ(edges)-1);
  edges.pb((edge){v,u,cap,0});
  G[v].pb(SZ(edges)-1);
}

bool bfs(){
  memset(vis,0,sizeof vis);
  vis[s];
  queue<ll> q;
  q.push(s);
  d[s] = 0;
  while(!q.empty()){
    ll u = q.front();q.pop();
    for(ll i=0;i<SZ(G[u]);i++){
      edge e = edges[G[u][i]];
      if(vis[e.v]||e.cap==e.flow)continue;s
      d[e.v] = d[u] + 1;
      vis[e.v] = 1;
      q.push(e.v);
    }
  }
  return vis[t];
}

ll dfs()
int main(){

}
