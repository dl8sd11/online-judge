#include <bits/stdc++.h>
using namespace std;

int t=1,m=100,n=100;
int rndnum(){
  return 1e8 + rand()%int(1e8);
}
int main(){
  cout<<t<<endl;
  while(t--){
    cout<<m<<" "<<n<<endl;
    for(int i=0;i<m;i++)cout<<rndnum()<<" ";
    cout<<endl;
    for(int i=0;i<m;i++)cout<<rndnum()<<" ";
    cout<<endl;
  }
}
