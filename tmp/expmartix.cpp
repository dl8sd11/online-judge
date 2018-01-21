#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(ll i=0;i<n;i++)
const ll MOD = int(1e9) +7;
int main() {
  ll n;
  cin>>n;
  if (n==1) {
    cout<<1<<endl;
    return 0;
  }
  bool roll = false;
  ll dp[2][2];
  dp[0][0] = 1;
  dp[0][1] = 1l;
  REP (i,n-1) {
    roll = !roll;
    dp[roll][1] = dp[!roll][1]*1+dp[!roll][0]*2;
    dp[roll][0] = dp[!roll][1]+dp[!roll][0]*4;
    dp[roll][0]%=MOD;
    dp[roll][1]%=MOD;

  }
  cout<<dp[roll][0]<<endl;
}
