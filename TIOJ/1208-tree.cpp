#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define SZ(u) ll(u.size())
#define MEM(i,m) memset(i,(m),sizeof(i))
#define ALL(i) i.begin(),i.end()
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template <typename T> void _do(T &&x) {cerr<<x<<endl;}
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '＼n'
#endif

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll MAXN = 200004;

ll n,k;
ll a[MAXN];

tree<pii,null_type,greater<pii>,rb_tree_tag,tree_order_statistics_node_update> rk;
ll solve(ll sum) {
  ll pre = 0;
  REP (i,n) {
    pre += a[i];
    rk.insert({pre,i});
  }

  pre = 0;
  ll ret = 0;
  REP (i,n) {
    ret += rk.order_of_key({sum+pre,-INF});
    pre += a[i];
    rk.erase({pre,i});
  }
  return ret;
}
/***********Good*Luck*************/
int main () {
  while (cin >> n >> k) {
    if (n == 0 && k == 0) {
      break;
    }
    REP (i,n) {
      cin >> a[i];
    }


    ll L = -200000007,R = 200000007;
    while (L < R - 1) {
      ll mid = (L+R)>>1;
      if (solve(mid) >= k) {
        L = mid;
      } else {
        R = mid;
      }
    }
    cout << L << endl;

    
  }
  return 0;
}