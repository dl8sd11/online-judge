#include <iostream>
#include <cmath>
#include <cstring>
#define FOR(a,b,c,d) for(int a=b;a<c;a+=d)
#define REP(i,n) FOR(i,0,n,1)
typedef long long ll;
using namespace std;

int t[1000];
int dp[1000][1000];
int solve(int st,int ed){
  if(dp[st][ed])
    return dp[st][ed];
  if(st==ed)
    return t[st];

  int left = 0;
  int sum = 0;
  FOR(i,st,ed+1,1)
    sum+=t[i];

  int cleft = sum - solve(st+1,ed);
  int cr = sum - solve(st,ed-1);
  int maxSol = max(cleft,cr);
  dp[st][ed] = maxSol;

  return maxSol;
}
int main(){
  int n;
  cin>>n;

  int sum =0;
  REP(i,n){
    cin>>t[i];
    sum+=t[i];
  }


  memset(dp,0,sizeof(dp));

  int first = solve(0,n-1);
  int second = sum-first;
  cout<<first<<' '<<second<<endl;


}
