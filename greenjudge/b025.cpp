#include <iostream>
using namespace std;


long solve(ll x,ll y){
  ll sum = x + y;
  if(x > y)swap(x,y);
  ll ret = 1;
  for(ll i=0;i<x;i++){
    if(ret%(i+1)==0){
      ret /= (i+1);
      ret *= (sum-i);
    } else if((sum-i)%(i+1)==0){
      ret *= (sum-i)/(i+1); 
    } else {
      ll tmptmp;
      (sum - i) /= __gcd((sum-i),(i+1));
      i+1 /= __gcd((sum-i),(i+1));
      ret /= __gcd((ret),(i+1));
      i+1 /= __gcd((ret),(i+1));
      ret *= ;
    }
  }
  return long(ret);
}
int main(){
  long long x,y;
  cin>>x>>y;
  cout<<solve(x,y)<<endl;
}
