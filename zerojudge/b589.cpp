#include <bits/stdc++.h>
using namespace std;
int n,a[100];
int dp[100][2];
int main(){
  while(cin>>n&&n!=0){
    memset(dp,0,sizeof(dp));
    for(int i=0;i<n;i++){
      cin>>a[i];
    }
    dp[0][0] = a[0];
    dp[0][1] = a[0]*2;
    for(int i=1;i<n;i++){
      dp[i][0] = max(dp[i-1][1],dp[i-1][0]+a[i]);
      dp[i][1] = dp[i-1][0]+a[i]*2;
    }
    cout<<max(dp[n-1][0],dp[n-1][1])<<endl;
  }
}
