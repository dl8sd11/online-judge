#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10000000;
vector<int> prime;
bool nPrime[MAXN];

void linear_sieve(int n){

  for(int i=2;i<n;i++){
    if(!nPrime[i])prime.push_back(i);
    for(int p:prime){
      if(p*i >= n)break;
      nPrime[i*p] = 1;
      if(i%p==0)break;
    }
  }
}
int main(){
  int n;
  cin>>n;
  linear_sieve(n);
  for(auto p:prime)cout<<p<<" ";
  cout<<endl;
}
