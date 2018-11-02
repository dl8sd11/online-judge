#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dp[100],l,r,ans;
int main() {
  cin>>l>>r;
  for(ll i=0;i<100;i++){
    if(i<3)dp[i] = i;
    else dp[i] = dp[i-1] + dp[i-2] + dp[i-3];
    if(dp[i] >= l && dp[i] <= r) ans++;
    if(dp[i] < 0 || dp[i] >= r)break;
  }

  cout<<ans<<endl;
}
