#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MAXN = 500;
const ll INF = 0x3f3f3f3f3f3f3f3f;
ll n,m,q;
ll a,b,v,s,t;
ll dis[MAXN][MAXN];

int main(){
  cin>>n>>m>>q;
  for(ll i=0;i<=n;i++)
    for(ll j=0;j<=n;j++)
      dis[i][j] = INF;

  for(ll i=0;i<m;i++)cin>>a>>b>>v,dis[a][b] = v;

  for (ll i=1; i<=n; i++)
    dis[i][i] = 0;

  for (ll k=1; k<=n; k++)
    for (ll i=1; i<=n; i++)
      for (ll j=1; j<=n; j++)
        if (dis[i][k] < INF && dis[k][j] < INF && dis[i][k] + dis[k][j] < dis[i][j])
            dis[i][j] = dis[i][k] + dis[k][j];

  while(q--){
    cin>>s>>t;
    if(dis[s][t]==INF)
      cout<<"No"<<endl;
    else
      cout<<dis[s][t]<<endl;
  }
}
