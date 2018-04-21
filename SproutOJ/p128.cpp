#include <bits/stdc++.h>
using namespace std;

void Report(int n){
  // cout<<n<<endl;
}
int ans[1025][1025];
void solve2(int N,int l,int t,int dl,int dr);
void solve1(int N,int l,int t,int dl,int dr){
  if(N==2){
    ans[t][l] = 1;
    ans[t+1][l+1] = 1;
    ans[t][l+1] = 2;
    ans[t+1][l] = 3;
    return;
  }
  // int dis = (dr-dl+1)/2;
  solve1(N/2,l,t,dl,(dl+dr-1)/2);
  solve1(N/2,l+N/2,t+N/2,dl,(dl+dr-1)/2);
  solve2(N/2,l+N/2,t,(dl+dr)/2,((dl+dr)/2+dr)/2);
  solve2(N/2,l,t+N/2,((dl+dr)/2+dr+1)/2,dr);
}
void solve2(int N,int l,int t,int dl,int dr){
  if(N==2){
    ans[t][l] = dl;
    ans[t+1][l+1] = dl;
    ans[t][l+1] = dr;
    ans[t+1][l] = dr;
    return;
  }
  //dl,(dl+dr-1)/2
  int dis = (dr-dl+1)/2;
  solve2(N/2,l,t,dl,dl+dis-1);
  solve2(N/2,l+N/2,t+N/2,dl,dl+dis-1);
  solve2(N/2,l+N/2,t,dl+dis,dr);
  solve2(N/2,l,t+N/2,dl+dis,dr);
}
void solve(int N){
  memset(ans,0,sizeof(ans));
  solve1(N,0,0,1,N*2-1);
  for(int i=0;i<N;i++)
    for(int j=0;j<N;j++)
      Report(ans[i][j]);
}
int main(){
  solve(1024);
  for(int i=0;i<1024;i++){
    for(int j=0;j<1024;j++){
      cout<<setw(4)<<ans[i][j]<<' ';
    }cout<<endl;
  }
}
