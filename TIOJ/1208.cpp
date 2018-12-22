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
const ll MAXN = 20004;
const ll MAXLG = __lg(MAXN)+3;

ll n,k;
ll a[MAXN];
ll BIT[MAXN];

ll query(ll idx) {
  ll ret = 0;
  for (;idx>0;idx-=idx&(-idx)) {
    ret += BIT[idx];
  }
  return ret;
}

void add (ll idx,ll val) {
  for (;idx<MAXN;idx+=idx&(-idx)) {
    BIT[idx] += val;
  }
}

ll solve(ll sum) {
  ll pre = 0;

  vector<ll> vx;
  map<ll,ll> mx;

  REP (i,n) {
    pre += a[i];
    vx.eb(pre);
  }

  sort(ALL(vx));
  vx.resize(unique(ALL(vx))-vx.begin());

  REP (i,SZ(vx)) {
    mx[vx[i]] = i+1;
  }

  pre = 0;
  REP (i,n) {
    pre += a[i];
    add(mx[pre],1);
  }

  pre = 0;
  ll ret = 0;
  REP (i,n) {
    ll q = upper_bound(ALL(vx),sum+pre-1)-vx.begin();
    ret += n-i-query(q);
    pre += a[i];
    add(mx[pre],-1);
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