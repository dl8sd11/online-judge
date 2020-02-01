#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for (ll i=0;i<n;i++)
#define REP1(i,n) for (ll i=1;i<=n;i++)
#define SZ(i) ll(i.size())
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
#define MEM(i,n) memset(i,(n),sizeof(i))
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define debug(...)
#define endl '\n'
#endif

const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll MAXN = 1e5+7;
ll n;
ll a[MAXN];
bool e[MAXN];
/*************Good*Luck******************/
int main() {
  cin >> n;
  ll mn = INF;
  ll mx = -INF;
  REP(i,n) {
    cin >> a[i];
    e[a[i]] = true;
    mn = min(mn,a[i]);
    mx = max(mx,a[i]);
  }

  bool flag = true;
  for (ll i=mn;i<=mx;i++) {
    if (!e[i]) {
      flag = false;
    }
  }

  cout << mn << " " << mx << " " << (flag?"yes":"no") << endl;
  return 0;
}













