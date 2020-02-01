#include <iostream>
using namespace std;
typedef long long ll;


ll m,d,l;
ll md(ll _m,ll _d){
  return (_m - 7)*31 + _d;
}
/********** Main()  function **********/
int main()
{

  cin>>m>>d>>l;
  if(md(8,30)-md(m,d) >= l){
    cout<<"YES"<<endl;
  } else {
    cout<<"NO"<<endl;
  }
  return 0;
}
