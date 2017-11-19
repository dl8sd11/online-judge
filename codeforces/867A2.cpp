#include <bits/stdc++.h>
#define FOR(a,b,c,d) for(a=b;a<c;a+=d
#define REP(i,n) FOR(i,0,n,1)
using namespace std;

int main(){
  int n;
  cin>>n;

  if(n==1){
    cout<<1<<' '<<1<<endl<<1<<endl;
  }
  else{
    cout<<(n-1)*2<<' '<<2<<endl;
    cout<<1<<' '<<2<<endl;
  }
}
