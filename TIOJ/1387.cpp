#include <bits/stdc++.h>
#include <vector>
#define REP(i,n) for(int i=0;i<n;i++)
#define pb push_back
#define X first
#define Y second
using namespace std;
int n,u,v,c,sz,t;
const int MAXN = 5003;
int w[MAXN],m[MAXN],dp[2][10003];
int main(){
  cin>>n;
  REP(i,n){
   cin>>u>>v>>c;
   REP (j,c) {
     w[sz] = u;
     m[sz++] = v;
   }
  }
  cin>>t;
  bool roll = false;
  dp[0][w[0]] = m[0];
  REP (i,sz-1) {
    roll = !roll;
    REP (j,t+1) {
      if (j-w[i+1]>=0) dp[roll][j] = max(dp[!roll][j],dp[!roll][j-w[i+1]]+m[i+1]);
      else dp[roll][j] = dp[!roll][j];
    }
  }
  int ans = 0;
  REP (i,t+1) ans = max(ans,dp[roll][i]);
  cout<<ans<<endl;
}
