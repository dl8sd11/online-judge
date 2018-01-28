#include <iostream>
#include <cmath>
#include <cstring>
#define FOR(a,b,c,d) for(int a=b;a<c;a+=d)
#define REP(i,n) FOR(i,0,n,1)
#define REP1(i,n) FOR(i,1,n+1,1)
typedef long long ll;
using namespace std;
const int MAXN = 5003;
bool t[MAXN][MAXN];
int dp[2][MAXN];
int tmp,l,w;
int main(){
  cin>>l>>w;
  while(l!=0&&w!=0){
    REP(i,l){
      REP(j,w){
        cin>>tmp;
        if(tmp==2) t[i][j] = 1;
        else t[i][j] = 0;
      }
    }
    bool roll = 0;
    int ans = 0;
    memset(dp,0,sizeof(dp));
    REP(i,w) if(t[0][i]) dp[0][i]=0;else dp[0][i]=1,ans=1;
    REP1 (u,l-1){
      roll = !roll;
      REP(i,w) {
        if (!i&&!t[u][i]) dp[roll][i] = 1;
        else dp[roll][i] = t[u][i]?0:(min(dp[roll][i-1],min(dp[!roll][i],dp[!roll][i-1]))+1);
        ans = max(ans,dp[roll][i]);
      }
    }
    cout<<ans*ans<<endl;
    cin>>l>>w;
  }

}
