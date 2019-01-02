#include <iostream>
using namespace std;

int n,c[200],sum,ans;
int main(){
  cin>>n;
  for(int i=0;i<n;i++){
    cin>>c[i];
    sum += c[i];
  }


  for(int i=0;i<n;i++){
    if(c[i] > sum/n){
      ans += c[i] - sum/n;
    }
  }

  cout<<ans<<endl;
}
