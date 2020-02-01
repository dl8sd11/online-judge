#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)

ll n,m,u,v,c;
const ll MAXN = 1003;
ll e[MAXN][MAXN];
int main(){
  cin>>n>>m;

  REP1(i,n){
    REP1(j,i){
      e[i][j] = (i-j)*100;
      e[j][i] = (i-j)*100;
    }
  }
  REP(i,m){
    cin>>u>>v>>c;
    e[u][v] = min(e[u][v],c);
    e[v][u] = min(e[v][u],c);
  }

  for(int k=1;k<=n;k++){
    for(int i=1;i<=n;i++){
      for(int j=1;j<=n;j++){
	e[i][j] = min(e[i][j],e[i][k]+e[k][j]);
      }
    }
  }

  cout<<e[1][n]<<endl;
}
