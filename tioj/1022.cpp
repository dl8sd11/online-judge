#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
#define MEM(i,n) memset(i,n,sizeof i)
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define X first
#define Y second
const ll MAXN = 3e3 + 7;
const ll INF = 1e18;
ll k,m,n;
ll h[103][103];
bool visit[103][103];
ll dirX[] = {-1,0,1,0};
ll dirY[] = {0,1,0,-1};
ll mabs(ll x) {return x<0?-x:x;}
int main(){
  cin>>k;
  while (k--) {
    MEM(visit,0);
    cin>>m>>n;
    REP (i,n+2) {
      visit[0][i] = 1;
      visit[m+1][i] = 1;
    }
    REP (i,m+2) {
      visit[i][0] = 1;
      visit[i][n+1] = 1;
    }
    REP1 (i,m) REP1(j,n) cin>>h[i][j];
    queue<pii> BFS;
    BFS.push({1,1});
    visit[1][1] = 1;
    ll cnt = 0;
    bool flag=0;
    while (BFS.size()) {
      ll sz = (ll)BFS.size();
      REP (u,sz) {
	pii now = BFS.front();BFS.pop();
       	if (now.X==m&&now.Y==n) {
	  cout<<cnt<<endl;
	  flag=1;
	  break;
	}
	REP (i,4) {
	  pii tmp = {now.X+dirX[i],now.Y+dirY[i]};
	  ll tx = tmp.X,ty = tmp.Y;
	  if (visit[tx][ty]||mabs(h[tx][ty]-h[now.X][now.Y])>5)continue;
	  BFS.push({tx,ty});
	  visit[tx][ty]=1;
	}
      }
      if (flag) break;
      cnt++;
    }
  }
}
