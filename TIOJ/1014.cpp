#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(ll i=0;i<n;i++)
ll dp[1<<16][16];
ll m[17];
ll n;
const ll INF = 1e18;
ll mabs(ll x) {return (x<0)?-x:x;}
ll solve(ll stat,ll idx) {
  ll ret = INF;
  if (dp[stat][idx]!=INF) return dp[stat][idx];
  REP (i,n) {
    if (i==idx) continue;
    if (((1<<i)&stat)==0) continue;
    if (dp[stat-(1<<idx)][i]==INF)dp[stat-(1<<idx)][i]=solve(stat-(1<<idx),i);
    ll tmp = ((dp[stat-(1<<idx)][i]+mabs(idx-i)-1)/m[idx]+1)*m[idx];
    ret = min(ret,tmp);
  }
  return ret;
}
 
int main() {

  cin>>n;
  REP(i,n){
    cin>>m[i];
  }
  REP (i,1<<16) {
    REP (j,16) {
      dp[i][j]=INF;
    }
  }


  REP (i,n) {
    dp[1<<i][i] = (i/m[i]+1)*m[i];
  }
  ll ans = INF;
  REP (i,n) {
    ans = min(solve((1<<n)-1,i),ans);
  }
  cout<<ans<<endl;
  return 0;
}
