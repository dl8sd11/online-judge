#include <bits/stdc++.h>
#define FOR(a,b,c,d) for(int a=b;a<c;a+=d)
#define REP(i,n) FOR(i,0,n,1)
using namespace std;

int main(){
  string a;
  cin>>a;
  int n;
  cin>>n;
  string w[n];
  bool f= false,s = false,b = false;
  REP(i,n){
    cin>>w[i];

    if(w[i]==a){
      cout<<"YES"<<endl;
      return 0;
    }
    if(w[i][0]==a[1])
      if(w[i][1]==a[0])
        b=true;
      else
        s=true;
    else if(w[i][1]==a[0])
      f=true;
  }
  if(b||(f&&s))
    cout<<"YES"<<endl;
  else
    cout<<"NO"<<endl;
}
