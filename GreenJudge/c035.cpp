#include <iostream>
#include <string>
using namespace std;

int main(){
  string input;
  cin>>input;

  int total = 0;
  for(int i=0;i<int(input.size());i++){
    if(input[i]=='S')
      total++;
  }


  double luck = total*1.0 / int(input.size());
  if(luck>=0.1)
    cout<<"EUROPE"<<endl;
  else if(luck<0.02)
    cout<<"AFRICA"<<endl;
  else
    cout<<"NORMAL"<<endl;

  return 0;
}
