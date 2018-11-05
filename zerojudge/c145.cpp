#include <bits/stdc++.h>
using namespace std;

int n,m;
int main() {
  cin>>n>>m;

  if(!(m&1)&&!(n&1)){
    cout<<max((n*2-1)*(m/2),(m*2-1)*(n/2))<<endl;
  } else if((m&1)&&(n&1)){
    int ret = 0;
    ret = max((n/2*4)*(m/2) + 1);
    ret = max((n/2*4)*(m/2) + 1);
    ret = 
  }else {
    if(m&1)swap(n,m);
    cout<<(n/2*4)*(m/2) + 1<<endl;
  }
}
