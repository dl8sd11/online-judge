#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back
#define X first
#define Y second
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
const ll MAXN = (ll)1e4 + 3;
const ll MAXlg = __lg(MAXN) + 2;
ll T,n,a,b,c,t;
ll par[MAXlg][MAXN],d[MAXN];
ll dis[MAXlg][MAXN],tin[MAXN],tout[MAXN];
vector<pii> e[MAXN];
void DFS(ll idx,ll p) {
  tin[idx] = t++;
  for(auto v:e[idx]) {
    if(v.X==p) continue;
    par[0][v.X]=idx;
    dis[0][v.X]=v.Y;
    d[v.X]=d[idx]+1;
    DFS(v.X,idx);
  }
  tout[idx] = t++;
}

bool isAncestor(ll x,ll y) {
  return tin[x]<=tin[y]&&tout[x]>=tout[y];
}
ll findLCA(ll x,ll y) {
  if(isAncestor(x,y))return x;
  if(isAncestor(y,x))return y;
  for(ll i=MAXlg-1;i>=0;i--) {
    if(!isAncestor(par[i][x],y))x=par[i][x];
  }
  return par[0][x];
}
pii kthAncestor(ll x,ll k) {
  ll retX=x,retY=0;
  for(ll i=MAXlg-1;i>=0;i--){
    if(d[x]-d[par[i][retX]]<=k)retY+=dis[i][retX],retX=par[i][retX];
  }
  return {retX,retY};
}
int main() {
  ios_base::sync_with_stdio(0);cin.tie(0);
  cin>>T;
  while(T--) {
    REP(i,n)e[i].clear();
    cin>>n;
    REP(i,n-1) {
      cin>>a>>b>>c;
      e[a].pb({b,c});
      e[b].pb({a,c});
    }
    d[1]=0;
    DFS(1,1);
    REP1(i,MAXlg-1)REP1(j,n)par[i][j]=par[i-1][par[i-1][j]],dis[i][j]=dis[i-1][j]+dis[i-1][par[i-1][j]];

    string cmd;
    while(cin>>cmd) {
      if(cmd=="DONE")break;
      cin>>a>>b;
      ll LCA = findLCA(a,b);
      if(cmd=="KTH") {
        cin>>c;
        c--;
        if(d[a]-d[LCA]>=c)cout<<kthAncestor(a,c).X<<endl;
        else cout<<kthAncestor(b,d[b]+d[a]-c).X<<endl;
      } else {
        cout<<kthAncestor(a,d[a]-d[LCA]).Y+kthAncestor(b,d[b]-d[LCA]).Y<<endl;
      }
    }
  }
}
