#include <iostream>
#include <cmath>
#include <cstring>
#define FOR(a,b,c,d) for(int a=b;a<c;a+=d)
#define REP(i,n) FOR(i,0,n,1)
typedef long long ll;
using namespace std;

int main(){
  int l,w;
  cin>>l>>w;

  bool t[l][w];
  while(l!=0&&w!=0){

    REP(i,l){
      REP(j,w){
        int tmp;
        cin>>tmp;
        if(tmp==2)
          t[i][j] = 1;
        else
          t[i][j] = 0;
      }
  }
  int dp[l][w];
  memset(dp,0,sizeof(dp));

  REP(i,l){
    if(t[i][0]==1)
    dp[i][0] = 0;
    else
    dp[i][0] = 1;
  }

  REP(i,w){
    if(t[0][i]==1)
    dp[0][i] = 0;
    else
    dp[0][i] = 1;
  }


  FOR(i,1,l,1){
    FOR(j,1,w,1){
      if(t[i][j]==1)
        dp[i][j]=0;
      else{
        int last = dp[i-1][j-1];
        if(last==0){
          dp[i][j] = 1;
        }
        else{
          int maxAns = min(dp[i-1][j],dp[i][j-1]);
          if(maxAns>last)
            maxAns = last;
          dp[i][j]=maxAns+1;



        }
      }
    }
  }
  int  Ans =0;
  REP(i,l){
    REP(j,w){
      // cout<<dp[i][j]<<' ';
      Ans = max(Ans,dp[i][j]);
    }

  }
  ll bA = Ans;
  cout<<bA*bA<<endl;
  cin>>l>>w;
}

}
