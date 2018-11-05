#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1000000007;

ll myexp(ll base,ll pw){
  if(pw==1)return base;
  ll tmp = myexp(base,pw/2);
  return (pw&1?tmp*tmp%MOD*base%MOD:tmp*tmp%MOD);
}

ll n,m;
int main(){
  cin>>n>>m;
  ll ans = 1;
  for(ll i=n;i>n-m;i--) ans = ans*i%MOD;
  for(ll i=1;i<=m;i++) ans = ans*myexp(i,MOD-2)%MOD;
  cout<<ans<<endl;
}
