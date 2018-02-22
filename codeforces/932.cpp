#include<bits/stdc++.h>
using namespace std;
int ans[1000003];
int main() {
  int n,a,b;
  cin>>n>>a>>b;
  int i,j;
  for (i=0;i*a<=n;i++) {
    if ((n-a*i)%b==0) {
      j = (n-a*i)/b;
      break;
    }
  }
  if (i*a>n) {
    cout<<-1<<endl;
    return 0;
  }  
  for (int k=1;k<=i*a;k++) {
    ans[k] = (k-1+i)%(a*i)+1;
  }
  for (int k=1;k<=j*b;k++) {
    ans[k+i*a] = (k-1+j)%(b*j)+1+i*a;
  }
  for (int t=1;t<=n;t++) cout<<ans[t]<<' ';
}
