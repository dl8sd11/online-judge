#include <bits/stdc++.h>
using namespace std;
#define REP1(i,n) for(int i=1;i<=n;i++)
int n;
int f[5003];
int main()
{
  cin>>n;
  REP1 (i,n) {
    cin>>f[i];
  }
  bool ans = 0;
  REP1 (i,n) {
    if (f[f[f[i]]]==i&&f[i]!=i)ans = 1;
  }
  if (ans) {
    cout<<"YES"<<endl;
  } else {
    cout<<"NO"<<endl;
  }
	return 0;
}
