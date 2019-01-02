#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
int t,n;
bool prime[500];

bool solve(int val){
  for(int i=2;i<val;i++)if(val%i==0&&i!=val/i&&prime[i]&&prime[val/i])return true;
  return false;
}
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);

  for (int i=2;i<500;i++) {
    prime[i] = 1;
    for (int j=2;j<i;j++) if(i%j==0) prime[i] = 0;
  }

  cin>>t;
  while(t--){
    cin>>n;
    bool ans = 0;
    for(int i=1;i<n;i++){
      if(solve(i)&&solve(n-i)) {
        ans = 1;
        #ifdef tmd
          cout<<"found "<<i<<endl;
        #endif
      }
    }
    if(ans==1)cout<<"YES"<<endl;
    else cout<<"NO"<<endl;
  }
}
