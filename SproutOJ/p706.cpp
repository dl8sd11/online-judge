#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<n;i++)
int main(){
  int n;
  vector<long long> a;
  cin>>n;
  long long tmp;
  REP(i,n-1){
    cin>>tmp;
    a.push_back(tmp);
  }
  sort(a.begin(),a.end());
  if(n==2){
    if(a[0]==1)cout<<2<<endl;
    else cout<<1<<endl;
    return 0;
  } else if(n==3){
    if(a[0]-a[1]+a[0]>0)cout<<a[0]-a[1]+a[0]<<endl;
    else if((a[1]-a[0])%2==0)cout<<(a[0]+a[1])/2<<endl;
    else cout<<a[n-2]+a[1]-a[0]<<endl;
    return 0;
  }else {
    bool flag = true;
    for(int i=2;i<n-1;i++){
      if(a[i]-a[i-1]!=a[1]-a[0])flag = false;
    }
    if(flag){
      if(a[0]-a[1]+a[0]>0)cout<<a[0]-a[1]+a[0]<<endl;
      else cout<<a[n-2]+a[1]-a[0]<<endl;
      return 0;
    } else {
      if(a[2]-a[1]<a[1]-a[0]) {
        cout<<(a[1]+a[0])/2<<endl;
        return 0;
      }else{
        for(int i=2;i<n-1;i++){
          if(a[i]-a[i-1]>a[1]-a[0]){
            cout<<(a[i]+a[i-1])/2<<endl;
            return 0;
          }
        }
      }
    }
  }
  while(1){}
}
