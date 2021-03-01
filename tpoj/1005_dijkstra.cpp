#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define X first
#define Y second
const int MAXN = 1000003;
const int INF = (int)0x3f3f3f3f;
int n,m,s,g,a,b,v;

int dis[MAXN];
bool vis[MAXN];
vector<pii> e[MAXN];
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  while(cin>>n>>m>>s>>g){
    REP(i,m){
      cin>>a>>b>>v;
      e[a].push_back({b,v});
    }

    // REP1(i,n)dis[i]=INF;
    memset(dis,INF,(n+1)*4);
    memset(vis,0,(n+1)*4);

    dis[s] = 0;
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    pq.push({0,s});
    REP(i,n){
      int found = -1;
      while(pq.size()&&vis[found=pq.top().Y])pq.pop();
      if(found==-1)break;
      vis[found]=1;
      for(auto vp:e[found]){
        if(dis[vp.X]>dis[found]+vp.Y){
          dis[vp.X] = dis[found]+vp.Y;
          pq.push({dis[vp.X],vp.X});
        }
      }
    }
    cout<<(dis[g]==INF?-1:dis[g])<<'\n';
  }
}
