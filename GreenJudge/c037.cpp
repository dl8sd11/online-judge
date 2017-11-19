#include <iostream>
using namespace std;

int abs(int n){
  if(n<0)return n*-1;
  else return n;
}
int main(){
  int n;
  cin>>n;

  int pos[n+1];
  for(int i=0;i<n;i++){
    int tmp;
    cin>>tmp;
    pos[tmp] = i;
  }

  int ans = 0;
  for(int i=2;i<=n;i++){
    ans+= abs(pos[i]-pos[i-1]);
  }
  cout<<ans<<endl;
}
