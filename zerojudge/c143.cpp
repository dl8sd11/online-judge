#include <bits/stdc++.h>
using namespace std;

int n,m,t;
int sx,sy,ex,ey;
bool tr[1000][1000];
int main() {
  cin>>n>>m>>t;
  while(t--){
    cin>>sx>>sy>>ex>>ey;
    int len = max(abs(sx-ex),abs(sy-ey));
    tr[sx][sy] = 1;
    for(int i=0,x=sx,y=sy;i<len;i++){
      x += (ex-sx)/len;
      y += (ey-sy)/len;
      tr[x][y] = 1;
    }
  }

  int ans = 0;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      ans += tr[i][j];

    }
  }

  cout<<ans<<endl;
}
