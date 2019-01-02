#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
#define X first
#define Y second
const ll MAXN = 103;
vector<pii> edge[MAXN];
ll t,n,m,mnbonus,bonus[MAXN],cnt[MAXN],u,v,delta,cur,ans;
queue<ll,list<ll> > bfs;
int main(){
	cin>>t;
	while(t--){
    cin>>n>>m>>mnbonus;
    for(ll i=1;i<=n;i++)bonus[i] = mnbonus;
    memset(cnt,0,sizeof cnt);
    for(ll i=1;i<=n;i++)edge[i].clear();
        
    for(ll i=0;i<m;i++){
       cin>>u>>v>>delta;
       edge[v].emplace_back(u,delta);
       cnt[u]++;
    }
    
    for(ll i=1;i<=n;i++)if(!cnt[i])bfs.emplace(i);
    
    while(bfs.size()){
      cur = bfs.front();bfs.pop();
      for(auto it:edge[cur]){
        if(--cnt[it.X]==0)bfs.emplace(it.X);
        bonus[it.X] = max(bonus[it.X],bonus[cur]+it.Y);
      }
    }
    
    bool flag = 0;
    for(ll i=1;i<=n;i++){
      if(cnt[i]!=0){
        cout<<"Inconsistent analysis."<<endl;
        flag = 1;
        break;
      }
    }      
    if(flag)continue;
    
    ans = 0;
    for(ll i=1;i<=n;i++) ans += bonus[i];
    cout<<ans<<endl;
    for(ll i=1;i<=n;i++){
      cout<<bonus[i]<<" \n"[i==n];
    }   
	}
	
}
