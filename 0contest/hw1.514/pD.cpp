#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define endl '\n'

const ll inf=0x3f3f3f3f3f3f3f3f;
void mx(ll &x,ll y){
    x=max(x,y);
}
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    vector<pair<int,int>> s(n);
    for(int i=0;i<n;i++){
        cin>>s[i].first>>s[i].second;
    }
    sort(s.rbegin(),s.rend());
    vector<vector<ll>> dp(2,vector<ll>(n+1,-inf));
    dp[1][1]=0;
    for(int i=0;i<n;i++){
        dp[i&1]=dp[i&1^1];
        for(int j=1;j<=n;j++){
            mx(dp[i&1][min(j+s[i].first-1,n)],dp[i&1^1][j]+s[i].second);
        }
    }

    ll ans=0;
    for(int i=0;i<=n;i++){
        mx(ans,dp[n&1^1][i]);
    }
    cout<<ans<<endl;
}
