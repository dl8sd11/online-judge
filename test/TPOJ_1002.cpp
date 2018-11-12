#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n,m,ans;
const ll MOD = 1000000007;
ll mypow (ll base,ll ex) {
  if(ex==0)return 1;
  ll tmp = mypow(base,ex/2);
  return ex&1?tmp*tmp%MOD*base%MOD:tmp*tmp%MOD;
}
int main () {
  cin>>n>>m;
  ans = 1;
  for (ll i=1;i<=m;i++) {
    ans = ans*(n-i+1)%MOD;
    ans = ans*mypow(i,MOD-2)%MOD;
  }

  cout<<ans<<endl;
}