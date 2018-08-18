#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10000000;
int a[MAXN],n,k;
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  cin>>n>>k;
  for(int i=0;i<n;i++)cin>>a[i];

  nth_element(a,a+k-1,a+n);
  cout<<a[k-1]<<" "<<endl;
}
