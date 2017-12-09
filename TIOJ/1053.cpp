#include <bits/stdc++.h>
using namespace std;

int main() {
  int n,m;
  cin>>n>>m;
  if(max(n,m) % min(n,m)) cout<<"N"<<endl;
  else cout<<"Y"<<endl;
}
