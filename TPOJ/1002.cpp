#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1000000007;
ll n,m;
ll myexp(ll b,ll p){
  if(p==1)return b;
  ll tmp = myexp(b,p/2);
  tmp = tmp*tmp%MOD;
  return p&1?tmp*b%MOD:tmp%MOD;
}
ll inv(ll a){
  return myexp(a,MOD-2);
}
int main(){
  cin>>n>>m;

  ll idx = 0;
  ll ans = 1;

  for(ll i=n;idx<m;){
    ans = ans *( i--) %MOD;
    ans = ans *inv(++idx) %MOD;


  }
  cout<<ans<<endl;
}
