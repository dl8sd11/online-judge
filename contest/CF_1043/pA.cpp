#include <bits/stdc++.h>
using namespace std;

int n,a[200],sum,mx;
int main() {
  cin>>n;
  for(int i=0;i<n;i++)cin>>a[i],sum += a[i],mx = max(mx,a[i]);
  int k;
  for(k=mx;k<=10000;k++){
    if(k*n > sum*2)break;
  }

  cout<<k<<endl;
}
