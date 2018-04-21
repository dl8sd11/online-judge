#include <bits/stdc++.h>
using namespace std;
int main(){
  int n,k;
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin>>n>>k;
  int m=n;
  while(k){
    if(__gcd(m,++n)==1)k--,cout<<n<<endl;
  }

}
