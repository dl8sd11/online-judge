#include <bits/stdc++.h>
using namespace std;


int main()
{
  for(int j=0;j<100;j++){
    int A[40] = {};
    const int n = rand()%40+1;
    long long  k = 0;
    for(int i=0;i<n;i++){
      A[i] = rand()%RAND_MAX+1;
      if(rand()&1)k+=A[i];
    }
    cout<<n<<' '<<k<<endl;
    for(int i=0;i<n;i++)cout<<A[i]<<' ';
  }
  return 0;

}
