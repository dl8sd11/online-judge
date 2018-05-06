#include <bits/stdc++.h>
using namespace std;

long long t,m,n;
long long a,b,c,tmp;
long long MOD = 1000000007;
int main(){
  cin>>t;
  while(t--){
    cin>>m>>n;
    a = 0,b = 0,c = 0;
    for(int i=0;i<m;i++)cin>>tmp,b+=tmp;
    b = ((b%MOD)*m) % MOD;
    for(int i=0;i<m;i++)cin>>tmp,c+=tmp;
    c = ((c%MOD)*m) % MOD;
    if(n==1)cout<<b<<endl;
    else if(n==2)cout<<c<<endl;
    else{
      for(int i=3;i<=n;i++){
        a = b;
        b = c;
        c = (a + b)%MOD;
      }
      cout<<c<<endl;
    }

  }
}
