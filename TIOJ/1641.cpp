#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define pb push_back
typedef int ll;
typedef pair<double,ll> pii;
#define REP(i,n) for(ll i=0;i<n;i++)
const ll MAXN = 10003;
ll n,m,s,t,a,b;
double c;
vector<pii> e[MAXN];
bool visit[MAXN];
double dis[MAXN];
priority_queue<pii,vector<pii>,greater<pii>> pq;

int main(){
  ios_base::sync
  cin>>n>>m>>s>>t;
  while(m--){
    cin>>a>>b>>c;
    e[a].pb({log10(c+1),b});
  }
  REP(i,n+1)dis[i]=100000;
  dis[s]=0;
  pq.push({0,s});
  while(pq.size()){
    pii now = pq.top();
    pq.pop();
    if(visit[now.Y])continue;
    for(auto i:e[now.Y]){
      if(dis[i.Y]>dis[now.Y]+i.X)dis[i.Y]=dis[now.Y]+i.X,pq.push({dis[i.Y],i.Y});
    }
    visit[now.Y]=1;
  }
  assert(dis[t]!=100000);
  ll head = ll(floor(dis[t]-1e-7)+1e-7);
  cout<<fixed<<setprecision(2)<<pow(10,dis[t]-head)<<"e+"<<setfill('0')<<setw(3)<<head<<endl;
}
