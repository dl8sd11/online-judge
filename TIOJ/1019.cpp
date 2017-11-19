#include <iostream>
#include <cmath>
#define FOR(a,b,c,d) for(int a=b;a<c;a+=d)
#define REP(i,n) FOR(i,0,n,1)
typedef long long ll;
using namespace std;
int main(){
  int t;
  cin>>t;
  REP(i,t){
    int n;
    cin>>n;

    ll x[n];
    REP(j,n)
      cin>>x[j];

    ll dp[n];
    dp[0]=0;
    dp[1]=abs(x[1]-x[0]);
    FOR(j,2,n,1){
      ll ost = abs(x[j]-x[j-1])+dp[j-1];
      ll tst = abs(x[j]-x[j-2])+dp[j-2];
      dp[j]=min(ost,tst);
    }
    cout<<dp[n-1]<<endl;

  }
}
