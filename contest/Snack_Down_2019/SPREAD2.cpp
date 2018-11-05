#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t,n,a,sum,idx,ans;

int main() {
  ios_base::sync_with_stdio(0);cin.tie(0);

  cin>>t;
  while (t--) {
    cin>>n;

    cin>>sum;
    ans = 0;
    idx = 1;

    while (idx < n) {
      ans++;
      ll tsum = 0;
      for (ll i = 0; i < sum && ++idx <= n; i++) {
        cin>>a;
        tsum += a;
      }
      sum += tsum;
    }


    cout<<ans<<"\n";
  }
}
