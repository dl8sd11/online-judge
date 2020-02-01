#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll t,n,ans;
int main() {
  cin>>t;
  while(t--){
    cin>>n;
    ans = 1;
    while(n){
      if(n&1)ans *= 2;
      n>>=1;
    }
    cout<<ans<<endl;
  }
}
