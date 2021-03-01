#include <bits/stdc++.h>
using namespace std;

int main(){
  int n,k,x;
  cin>>n>>k>>x;

  int ans =0;
  for(int i=0;i<n;i++){
    int tmp;
    cin>>tmp;
    if(i<(n-k))ans += tmp;
    else ans += x;
  }
  cout<<ans<<endl;
}
