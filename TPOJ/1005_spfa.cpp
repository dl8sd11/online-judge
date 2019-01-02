#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define X first
#define Y second
const int MAXN = 1000003;
const int INF = (int)0x3f3f3f3f;
int n,m,s,g,a,b,c;

int dis[MAXN];
vector<pii> e[MAXN];
struct que{
  int ar[540000];
  int head,tail;
  que(){head=0;tail=0;}
  void push(int x){
    ar[tail++]=x;
  }
  void pop(){
    head++;
  }
  int front(){
    return ar[head];
  }
  int size(){
    return tail-head;
  }
};
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  while(cin>>n>>m>>s>>g){
    REP(i,m){
      cin>>a>>b>>c;
      e[a].push_back({b,c});
    }

    memset(dis,INF,(n+1)*4);
    dis[s] = 0;

    que q;
    q.push(s);
    while(q.size()){
      for(auto v:e[q.front()]){
        if(dis[v.X] > dis[q.front()] + v.Y){
          dis[v.X] = dis[q.front()] + v.Y;
          q.push(v.X);
        }
      }
      q.pop();
    }
    cout<<(dis[g]==INF?-1:dis[g])<<'\n';
  }
}
