#include <bits/stdc++.h>
using namespace std;

int t,n;
int main(){
  cin>>t;
  while(t--){
    cin>>n;
    int ans = 0,tmp;
    while(n--){
      cin>>tmp;
      ans = ans ^ (tmp*2);
    }
    cout<<ans<<endl;
  }
}
