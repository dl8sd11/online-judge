#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f(x) ((x*x+c)%n)

ll mypow(ll base,ll exp,ll md){
  if(exp==1)return base % md;
  ll hlf = mypow(base,exp>>1,md);
  return (exp&1?hlf*hlf%md*base%md:hlf*hlf%md);
}
bool miller_rabin(ll n,ll a){
  if(n<2)return false;
  ll u = n-1,t = 0;
  while(!(u&1))u>>=1,t++;
  ll x = mypow(a,u,n);
  if(x==1||x==n-1)return true;
  for(ll i=0;i<t-1;i++){
    x = x*x%n;
    if(x==1)return false;
    if(x==n-1)return true;
  }
  return false;
}
bool isprime(ll n){
  vector<ll> a = {2,3,5,7,11,13,17,19,23,29,31,37};
  if (n < 1000) {
      for (int i=2;i*i<=n;i++) {
          if (n % i == 0) {
              return false;
          }
      }
      return true;
  }
  bool ret = 1;
  for(ll i=0;i<a.size();i++){
    if(a[i]!=n)ret &= miller_rabin(n,a[i]);
  }
  return ret;
}


ll pollard_rho(ll n,ll c){
  if (n < 1000) {
      for (int i=2;i*i<=n;i++) {
          if (n % i == 0) {
              return i;
          }
      }
      return n;
  }
  ll a0 = rand()%(n-1)+1;
  ll x = a0,y = a0;
  while(true){
    x = f(x);y = f(f(y));
    if(x==y)return n;
    ll d = __gcd(abs(x-y),n);
    if(d>1&&d<n)return d;
  }
  return -1;
}

vector<ll> factor;
void factorize(ll n){
  if(n==1)return;
  if(isprime(n)){
    factor.push_back(n);
    return;
  }
  ll d = n;

  for(ll c=0;d==n;++c)
    d = pollard_rho(n,c);
  factorize(d);
  factorize(n/d);
}
int main(){
  int tmp;
  cin>>tmp;
  factor.clear();
  factorize(tmp);
  for(ll i=0;i<factor.size();i++)cout<<factor[i]<<" ";
  
}