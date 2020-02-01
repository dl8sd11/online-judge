#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define IOS ios_base::sync_with_stdio(0);cin.tie(0)
#define endl '\n'

const ll MOD = 1000000007;
ll mul(ll _a,ll _b){
  return (_a * _b)%MOD;
}

ll add(ll _a,ll _b) {
  return (_a + _b)%MOD;
}

ll mypow(ll base,ll e) {
  if(e==1)return base;
  if(e==0)return 1;
  ll tmp = mypow(base,e/2);
  return (e&1)?(mul(mul(tmp,tmp),base)):(mul(tmp,tmp));
}

ll inv(ll base) {
  return mypow(base,MOD-2);
}
vector<ll> v;
ll t,n,a[100003],cnt,ans;
int main () {
  cin>>t;
  while(t--){
    cin>>n;
    for(ll i=0;i<n;i++)cin>>a[i];
    sort(a,a+n);

    v.clear();
    cnt = 1;
    for (ll i=1;i<=n;i++) {
      if (i==n||a[i]!=a[i-1]) {
        v.emplace_back(cnt);
        cnt = 1;
      } else {
        cnt++;
      }
    }

    ans = 1;
    for (ll i=v.size()-1;i>=0;i--) {
      if (v[i]&1) {
        assert(i!=0);
        ans = mul(ans,mul(v[i],v[i-1]));
        v[i]--;
        v[i-1]--;
      }
      for (ll j=1;j<=v[i];j++) {
        ans = mul(ans,j);
        if(!(j&1))ans = mul(ans,inv(j/2));
      }

      ans = mul(ans,inv(mypow(2,v[i]/2)));
    }


    cout<<ans<<endl;
  }
}
