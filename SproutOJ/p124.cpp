#include <bits/stdc++.h>
using namespace std;
void Report(int a,int b,int c,int d,int e,int f){
  cout<<"Report("<<a<<","<<b<<","<<c<<","<<d<<","<<e<<","<<f<<");"<<endl;
}
void solve(int l,int t,int N,int X,int Y){
  int dir = (X>=N/2+l)+(Y>=N/2+t)*2;
  vector<pair<int,int> > mid = {{l+N/2-1,t+N/2-1},{l+N/2,t+N/2-1},{l+N/2-1,t+N/2},{l+N/2,t+N/2}};
  vector<pair<int,int> > newPos = {{l,t},{l+N/2,t},{l,t+N/2},{l+N/2,t+N/2}};
  if(N==2){
    vector<int> fillAr;
    for(int i=0;i<4;i++)if(i!=dir)fillAr.push_back(newPos[i].first),fillAr.push_back(newPos[i].second);
    Report(fillAr[0],fillAr[1],fillAr[2],fillAr[3],fillAr[4],fillAr[5]);
    return;
  }
  vector<int> reportAr;
  for(int i=0;i<4;i++){
    if(dir!=i) {
      reportAr.push_back(mid[i].first);
      reportAr.push_back(mid[i].second);
      solve(newPos[i].first,newPos[i].second,N/2,mid[i].first,mid[i].second);
    }else solve(newPos[i].first,newPos[i].second,N/2,X,Y);
  }
  Report(reportAr[0],reportAr[1],reportAr[2],reportAr[3],reportAr[4],reportAr[5]);
}
void solve(int N,int X,int Y){
  solve(1,1,N,X,Y);
}
int main(){
  solve(4,3,4);
}
