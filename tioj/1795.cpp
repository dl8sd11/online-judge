#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define X first
#define Y second
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
const int MAXN = int(1e5) + 3;
int n,m,k,xi,yi;
bool c;
vector<pii > e[2];
int dis[MAXN],sz[MAXN];
int find(int x) {return (x==dis[x])?x:dis[x]=find(dis[x]);}
void Union(int x,int y) {
  if (sz[x=find(x)]<sz[y=find(y)])swap(x,y);
  dis[y] = x;
  sz[x] = sz[x] + sz[y];
}
int MST(bool start) {
  REP1(i,n) dis[i]=i,sz[i]=1;
  int ret = 0;
  for (auto v:e[start]) {
    if (find(v.X)!=find(v.Y)) {
	Union(v.X,v.Y);
	ret+=start;
    }
  }
  start = !start;
  for (auto v:e[start]) {
    if (find(v.X)!=find(v.Y)) {
	Union(v.X,v.Y);
	ret+=start;
    }
  }
    return ret;
}
int main() {
  cin>>n>>m>>k;
  REP (i,m) {
    cin>>xi>>yi>>c;
    e[c].push_back({xi,yi});
  }
  if (k>=MST(0)&&k<=MST(1)) cout<<"TAK"<<endl;
  else cout<<"NIE"<<endl;
}
