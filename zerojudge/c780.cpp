#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


ll n,m,cnt;
bool state[10][10];
ll DFS(ll x,ll y){
  ll ret = 0;
  cnt = 0;
  for(ll i=x;i<n;i++){
    if(!state[i][y])cnt++;
    if(cnt == 2){
      state[i][y] = 1;
      ret = max(ret,DFS(i,y));
      state[i][y] = 0;
      break;
    }
  }

  cnt = 0;
  for(ll i=x;i>=0;i--){
    if(!state[i][y])cnt++;
    if(cnt == 2){
      state[i][y] = 1;
      ret = max(ret,DFS(i,y));
      state[i][y] = 0;
      break;
    }
  }

  cnt = 0;
  for(ll i=y;i>=0;i--){
    if(!state[x][i])cnt++;
    if(cnt == 2){
      state[x][i] = 1;
      ret = max(ret,DFS(x,i));
      state[x][i] = 0;
      break;
    }
  }

  cnt = 0;
  for(ll i=y;i<m;i++){
    if(!state[x][i])cnt++;
    if(cnt == 2){
      state[x][i] = 1;
      ret = max(ret,DFS(x,i));
      state[x][i] = 0;
      break;
    }
  }

  cnt = 0;
  return ret + 1;
}
int main() {
  cin>>n>>m;
  cout<<n<<" "<<m<<endl;
  state[0][0] = 1;
  // cout<<DFS(0,0)-1<<endl;
}
