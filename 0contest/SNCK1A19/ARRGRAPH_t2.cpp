#include <bits/stdc++.h>
using namespace std;

int a[50];
int n = 7;
int main() {
  cout<<n<<endl;
  for(int i=0;i<n;i++)a[i]=rand()%49+1;
  for(int i=0;i<n;i++){
    for(int j=i+1;j<n;j++){
      if(__gcd(a[i],a[j])==1){
        cout<<i<<" "<<j<<endl;
      }
    }
  }
}
