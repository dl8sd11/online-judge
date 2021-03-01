#include <bits/stdc++.h>
using namespace std;

int main(){
  int n,k;
  cin>>n>>k;

  int know[k];
  memset(know,0,sizeof(know));
  for(int i=0;i<n;i++){
    for(int j=0;j<k;j++){
      bool tmp;
      cin>>tmp;
      know[j]+=int(tmp);
    }
  }


  bool ans = true;
  int half = int(ceil(double(n)/2));
  for(int i=0;i<k;i++){
    if(know[i]<half){
      ans = false;
      break;
    }
  }
  if(ans){
    cout<<"Yes"<<endl;
  }
  else{
    cout<<"No"<<endl;
  }
}
