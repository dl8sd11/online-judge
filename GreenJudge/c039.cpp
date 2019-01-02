#include <iostream>
using namespace std;
typedef long long ll;

ll a,b;
/********** Main()  function **********/
int main()
{
  cin>>a>>b;
  if(a<=29){
    cout<<1<<" ";
  } else if(a <= 49){
    cout<<2<<" ";
  } else if(a<=69){
    cout<<3<<" ";
  } else if(a<=89){
    cout<<4<<" ";
  } else if(a<=100){
    cout<<5<<" ";
  }

  if(b<=49){
    cout<<1<<endl;
  } else if(b <= 149){
    cout<<2<<endl;
  } else if(b<=249){
    cout<<3<<endl;
  } else if(b<=349){
    cout<<4<<endl;
  } else if(b<=400){
    cout<<5<<endl;
  }

  return 0;
}
