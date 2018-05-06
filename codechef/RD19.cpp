#include <bits/stdc++.h>
using namespace std;

int t,n,a[1003];
int main(){
  cin>>t;
  while(t--){
    cin>>n;
    int gcd,tmp;
    cin>>gcd;
    for(int i =0;i < n-1;i++)cin>>tmp,gcd=__gcd(tmp,gcd);
    if(gcd==1)cout<<0<<endl;
    else cout<<-1<<endl;
  }
}
