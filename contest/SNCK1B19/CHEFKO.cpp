#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef long long ll;
#define REP(i,n) for(ll i=0;i<n;i++)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)

ll t,k,n,l,r,ans;
vector<pair<ll,ll> > seg;
tree<pair<ll,ll> ,null_type,greater<pair<ll,ll> >,rb_tree_tag,tree_order_statistics_node_update> rktree;

int main() {
  IOS();
  cin>>t;
  while (t--){
    ans = 0;
    seg.clear();
    rktree.clear();

    cin>>n>>k;
    REP (i,n) cin>>l>>r,seg.emplace_back(l,r);
    sort(seg.begin(),seg.end());

    REP (i,k-1) rktree.insert({seg[i].second,i});
    for (ll i=k-1;i<n;i++) {
      rktree.insert({seg[i].second,i});
      ans = max(ans,((*rktree.find_by_order(k-1)).first)-seg[i].first);
    }

    cout<<ans<<endl;
  }
  return 0;
}
