#include <bits/stdc++.h>
#define FOR(a,b,c,d) for(int a=b;a<c;a+=d)
#define REP(i,n) FOR(i,0,n,1)
using namespace std;

int main(){
  int h, m, s, t1, t2;
  cin>>h>>m>>s>>t1>>t2;

  h*=5;
  t1*=5;
  t2*=5;

  int amin = min(m,s);
  int amax = max(m,s);

  double p1 = h;
  double p2 = h + (amax-amin)/60;

  int a[3]={h,m,s};
  sort(a,a+3);
  //cout<<a[0]<<' '<<a[1]<<' '<<a[2]<<endl;

  if(t1>=a[0]&&t2>=a[0]&&t1<=a[1]&&t2<=a[1]){
    cout<<"YES"<<endl;
  }
  else if(t1>=a[1]&&t2>=a[1]&&t1<=a[2]&&t2<=a[2]){
    cout<<"YES"<<endl;
  }
  else if(t1>=a[2]&&t2>=a[2]&&t1<=a[1]&&t2<=a[1]){
    cout<<"YES"<<endl;
  }
  else if(t1>=p1&&t2>=p1&&t1<=p2&&t2<=p2){
    cout<<"YES"<<endl;
  }
  else{
    cout<<"NO"<<endl;
  }
}
