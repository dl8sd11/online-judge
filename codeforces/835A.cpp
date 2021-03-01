#include <iostream>
using namespace std;

int main(){
  int a,b,c,d,e;
  cin>>a>>b>>c>>d>>e;
  int first = a*b+d*2;
  int second = a*c+e*2;

  if(first <second){
    cout<<"First"<<endl;
  }
  else if(first > second){
    cout<<"Second"<<endl;
  }
  else{
    cout<<"Friendship"<<endl;
  }
}
