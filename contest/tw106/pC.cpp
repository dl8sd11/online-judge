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
ll n;
ll ab[3][3];
vector<ll> ar[3];
ll cnt[3][10];
/*************Good*Luck******************/
int main() {
  IOS();
  cin >> n;
  REP(j,n) {
    ll g;
    bool b;
    cin >> g;
    g--;

    ll sum = 0,base = 1;
    REP (i,3) {
      cin >> b;
      sum += b*base;
      base <<= 1;
    }
    ar[g].emplace_back(sum);
    REP (i,9) {
      if ((i&sum)==i) {
	cnt[g][i]++;
      }
    }
  }

  ll ans = 0;
  REP (i,SZ(ar[0])) {
    REP (j,SZ(ar[1])) {
      ll cv = ar[0][i] | ar[1][j];
      ans += cnt[2][7-cv];
    }
  }

  cout << ans << endl;
  return 0;
}


