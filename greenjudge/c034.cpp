#include <iostream>
using namespace std;

int nextNum(int current){
  int ret = 0;
  current = (current*7)%100;
  ret += current/10 + current%10*10;
  return ret;
}
int main(){
  int a,n;
  cin>>a>>n;
  for(int i=0;i<n;i++){
    a = nextNum(a);
  }
  cout<<a<<endl;

}
