#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double lf;
typedef pair<ll,ll> ii;
#define MEM(a) memset(a,(0),sizeof(a))
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define FILL(i,n) memset(i,n,sizeof i)
#define X first
#define Y second
#define SZ(_a) (int)_a.size()
#define ALL(_a) _a.begin(),_a.end()
#define pb push_back
#define mp make_pair
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);

int mod = 1000000;
int main(){
  IOS();
  int dp[208][208]; // dp[i][j] i 箱 j 球 至少1 each

  REP(i,207){
    REP(j,208){
      dp[i][j] = 1;
    }
  }

  for(int i=2;i<=207;i++){
    for(int j=i;j<=207;j++){
      if(j!=i)dp[i][j] = (dp[i-1][j-1] + ((dp[i][j-1])*i)%mod) % mod;
    }
  }


  int n,m;
  cin>>n>>m;
  while(n&&m){
    int ans = 0;
    for(int i=1;i<=n;i++){
      if(i<=m){

        ans += dp[i][m];
        ans %= mod;
      }
    }
    cout<<ans<<endl;
    cin>>n>>m;
  }

}
