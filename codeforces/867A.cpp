#include <bits/stdc++.h>
#define FOR(a,b,c,d) for(a=b;a<c;a+=d
#define REP(i,n) FOR(i,0,n,1)
using namespace std;

int main(){
  int n;
  cin>>n;
  char p[n];
  cin>>p;

  if(p[0]=='S'&&p[n-1]!='S')
    cout<<"YES"<<endl;
  else
    cout<<"NO"<<endl;

}
