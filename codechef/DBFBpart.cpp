#include <bits/stdc++.h>
using namespace std;

long long t,m,n;
long long MOD = 1000000007;
long long a[100000],b[100000];
long long fib[100000];
int solve(int i,int j){
  fib[0] = a[i];
  fib[1] = b[j];
  for(int x=2;x<n;x++){
    fib[x] = fib[x-1] + fib[x-2];
    fib[x] %= 1000000007;
  }
  return fib[n-1];
}
int main(){
  cin>>t;
  while(t--){
    cin>>m>>n;
    long long result = 0;
    for(int i=0;i<m;i++)cin>>a[i];
    for(int i=0;i<m;i++)cin>>b[i];
    for(int i=0;i<m;i++){
      for(int j=0;j<m;j++){
        result += solve(i,j);
        result %= MOD;
        //printf("(%d,%d) = %d",i,j,result);
      }
    }
    cout<<result<<endl;
  }
}
