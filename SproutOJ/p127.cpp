#include <bits/stdc++.h>
using namespace std;
int val[4][5]= {{74,59,36,28,51},{36,63,15,25,17},{71,64,95,43,56},{72,62,30,24,74}};
int ans[1000003];
int GetVal(int n,int m){return val[n-1][m-1];}
int GetPos(int l,int r,int row){ //maxpos in [l,r]
  if(l==r)return l;
  int mx = -1,mxpos = -1,tmp;
  for(int i=l;i<=r;i++){
    tmp=GetVal(row,i);
    if(tmp>mx)mx=tmp,mxpos=i;
  }
  return mxpos;
}
void solve(int l,int r,int t,int d){
  if(t==d){
    ans[t]=GetPos(l,r,t);
    return;
  } else if(d<t)return;
  int mid = (t+d)/2;
  ans[mid]=GetPos(l,r,mid);
  solve(l,ans[mid]-1,t,mid-1);
  solve(ans[mid]+1,r,mid+1,d);
}
void solve(int N,int M){
  memset(ans,0,sizeof(ans));
  solve(1,M,1,N);
  for(int i=1;i<=N;i++)Report(ans[i]);
}
int main(){
  solve(4,5);
}
