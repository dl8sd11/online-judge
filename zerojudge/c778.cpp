#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
int n,m,l,ans;
int sn,sm,dn,dm;
int dp[103][103][1003],mn[103][103];
int main(){
  cin>>n>>m>>l;
  if(m%l > n%l)swap(n,m);
  sn = m/l +1;
  sm = n/l;
  dn = n%l;
  dm = m%l;
  memset(dp,INF,sizeof dp);
  memset(mn,INF,sizeof mn);
  dp[0][0][0] = 0;
  for(int i=0;i<=sn;i++){
    for(int j=0;j<=sm;j++){
      for(int k=0;k<=l;k++){
        if(i!=0){
          if(k==dn)dp[i][j][k] = min(dp[i][j][k],mn[i-1][j]+1);
          dp[i][j][k] = min(dp[i][j][k],(k<dn?INF:dp[i-1][j][k-dn]));
        }
        if(j!=0){
          if(k==dm)dp[i][j][k] = min(dp[i][j][k],mn[i][j-1]+1);
          dp[i][j][k] = min(dp[i][j][k],(k<dm?INF:dp[i][j-1][k-dm]));
        }
        cout<<i<<" "<<j<<" "<<k<<" "<<dp[i][j][k]<<endl;
        mn[i][j] = min(dp[i][j][k],mn[i][j]);
      }
    }
  }
  ans = INF;
  for(int i=0;i<=l;i++){
    ans = min(ans,dp[sn][sm][i]);
  }
  cout<<ans + sn*sm<<endl;
}
