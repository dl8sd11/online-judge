#include <bits/stdc++.h>
using namespace std;

int a,b,c,d;
int m,s,t;

int disInTime(int nm,int ns,int nt,int bt){ //now gas, now dis, now time, boost time
  nm += bt*d;
  nt -= bt;
  if(nm/c>=nt){ //boost all time
    return nt*b;
  } else {
    return nm/c*b+(nt-nm/c)*a;
  }
}
int timeToWin(int nm,int ns,int nt,int bt){
  nm += bt*d;
  nt -= bt;
  //cout<<"DE "<<(ns-nm/c*b)<<endl;
  if(nm/c*b>=ns){ //boost all way
    return ceil(double(ns)/b)+bt;
  } else {
    return ceil(double(ns-nm/c*b)/a)+bt+nm/c;
  }
}
int main(){
  cin>>a>>b>>c>>d;
  cin>>m>>s>>t;
  int maxDis = 0;
  int minTime = 1000000000;
  for(int i=0;i<t;i++){
    int dit = disInTime(m,s,t,i);
    if(dit>=s){
      minTime = min(minTime,timeToWin(m,s,t,i));
      //cout<<i<<" "<<timeToWin(m,s,t,i)<<endl;
    } else {
      maxDis = max(maxDis,dit);
    }
  }
  if(minTime!=1000000000){
    cout<<"Yes"<<endl;
    cout<<minTime<<endl;
  } else {
    cout<<"No"<<endl;
    cout<<maxDis<<endl;
  }

}
