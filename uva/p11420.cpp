#include <bits/stdc++.h>
using namespace std;

int dp[70][70][2];
int main(){
  int n,s;
  while(cin>>n>>s&&n!=-1){
    memset(dp,0,sizeof(dp));
    dp[1][0][0] = 1;
    dp[1][0][1] = 1;
    for(int i=2;i<=n;i++){
      for(int j=0;j<=s;j++){
        dp[i][j][1] = dp[i-1][j][0] + (j!=0?dp[i-1][j-1][1]:0);
        dp[i][j][0] = dp[i-1][j][0] + dp[i-1][j][1];
      }
    }
    for(int i=1;i<=n;i++){
      for(int j=0;j<=s;j++){
        cout<<dp[i][j][0]+dp[i][j][1]<<' ';
      }
      cout<<endl;
    }
    cout<<dp[n][s][0] + dp[n][s][1]<<endl;
  }
}
