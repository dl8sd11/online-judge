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


int m,n;
int main(){
  IOS();
  cin>>m>>n;
  REP(i,m){
    int num[n];
    int sum = 0;
    int MAXN = 0;
    REP(j,n){
      cin>>num[j];
      MAXN = max(MAXN,num[j]);
      sum += num[j];
    }
    if(sum&1){
      cout<<"No"<<endl;
      continue;
    }
    const int SZ = MAXN*n/2+7;
    bool dp[2][SZ];
    MEM(dp);
    bool roll = 0;
    dp[0][0] = true;
    dp[0][num[0]] = true;
    REP1(j,n-1){
      roll = !roll;
      REP(k,MAXN*n/2+5){
        bool q;
        if(k-num[j]>=0){
          q = dp[!roll][k-num[j]];
        }
        else{
          q = false;
        }
        dp[roll][k] = dp[!roll][k] | q;
      }
    }
    if(dp[roll][sum/2]) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
  }
}
