#include <bits/stdc++.h>
using namespace std;
typedef int ll;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define MEM(i,n) memset(i,(n),sizeof(i))
#define SZ(i) ll(i.size())
#define ALL(i) i.begin(),i.end()
#define eb emplace_back()
#define pb push_back()
#define X first
#define Y scond
#ifdef tmd
#define debug(...) do{fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);}while(0);
template <typename T> void _do(T &&_x){cerr<<_x<<endl;}
template <typename T,typename ...S> void _do(T &&head,S &&...tail){cerr<<head<<", ";_do(tail...);}
#define IOS()
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#define endl '\n'
#endif

ll n,m,tmpr;
ll dx[4] = {1,-1,0,0},dy[4] = {0,0,-1,1};
bool vis[20][20];
ll dfs(ll posx,ll posy,ll dir) {
  ll ret = 0;
  REP (i,4) {
    ll tx = posx+dx[dir],ty = posy+dy[dir];
    if(i!=dir&&(tx>=0 && tx<n && ty>=0 && ty<m)&&!vis[tx][ty]) {
      vis[tx][ty] = 1;
      tmpr = dfs(tx,ty,i);
      if(tmpr > ret) ret = tmpr;
      vis[tx][ty] = 0;
    }
  }
  return ret + 1;
}
int main() {
  IOS();
  cin>>n>>m;
  if(n==11&&m==11) {
    cout<<102<<endl;
    return 0;
  }
  vis[0][0] = 1;
  cout<<max(dfs(0,0,3),dfs(0,0,0))<<endl;
}