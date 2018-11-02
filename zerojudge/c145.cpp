#include <bits/stdc++.h>
using namespace std;

int n,m;
int main() {
  cin>>n>>m;

  if(!(m&1)&&!(n&1)){
    if(n>m)n--;
    else m--;
  }
  if(m&1)swap(n,m);
  cout<<(n/2*4)*(m/2) + 1<<endl;
}
