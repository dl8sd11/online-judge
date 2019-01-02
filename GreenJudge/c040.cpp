#include <iostream>
using namespace std;
typedef long long ll;
ll a,b;

ll gcd(ll x,ll y){
  if(y==0)return x;
  cout<<x<<"%"<<y<<"="<<x%y<<endl;
  return gcd(y,x%y);
}
int main(){
  cin>>a>>b;
  ll ans = gcd(a,b);
  cout<<"GCD("<<a<<","<<b<<")="<<ans<<endl;
}
