#include <bits/stdc++.h>
using namespace std;

int t,n,a[100003];
bool solve(int len){
  if(len==0)return 1;
  bool ret = 1;
  for(int i=0;i<n;i++){
    if(a[i]!=-1 && a[i] != (i%len)+1)ret = 0;
  }
  return ret;
}
int main() {
  cin>>t;
  while(t--){
    cin>>n;
    for (int i=0;i<n;i++) cin>>a[i];
dd
    int l = 0, r = 100010;
    while(l < r - 1) {
      int mid = (l+r) / 2;
      if(solve(mid))l = mid;
      else r = mid;
    }
    if(l==0)cout<<"impossible\n";
    else if(l > n)cout<<"inf\n";
    else cout<<l<<endl;
  }
}
