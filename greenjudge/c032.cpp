#include <iostream>
using namespace std;

int main(){
  int a,b;
  cin>>a>>b;

  int ans =0;
  if(a>=60){
    ans++;
  }
  if(b>=60){
    ans++;
  }

  if(a+b>=120){
    ans = 2;
  }
  cout<<ans<<endl;
}
