#include <bits/stdc++.h>
using namespace std;

int n;
bool sieve[10000003];
vector<int> prime;

int main(){
  cin>>n;
  for (int i=2;i<n;i++) {
    if (!sieve[i]) prime.push_back(i);
    for(int j=0;prime[j]*i<n;j++){
      sieve[prime[j]*i] = 1;
      if(i%prime[j] == 0)break;
    }
  }
  for(auto num:prime)cout<<num<<" ";
  cout<<endl;
}
