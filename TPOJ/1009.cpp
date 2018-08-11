#include <bits/stdc++.h>
using namespace std;

int z[1000000];
string a,b;

void z_build(){
  z[0] = 0;
  for(int i=1, bst=0;a[i];i++){
    if(bst+z[bst]<i)z[i]=0;
    else z[i]=min(z[i-bst],bst+z[bst]-i);
    while(a[z[i]]==a[z[i]+i])z[i]++;
    if(i+z[i]>bst+z[bst])bst = i;
  }
}
int main(){
  cin>>a>>b;
  int n = a.size();
  a = a + char(255) + b;
  z_build();
  int ans = 0;
  for(int i=n+1;a[i];i++){
    if(z[i]==n)ans++;
  }
  cout<<ans<<endl;
}
