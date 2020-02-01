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

ll b;
string n;

ll mpow(ll base,ll ex) {
  ll ret = 1;
  REP (i,ex) {
    ret *= base;
  }

  return ret;
}
/*************Good*Luck******************/
int main() {
  IOS();
  cin >> b >> n;
  ll sum1 = 0,sum2 = 0;
  ll base = 1;
  for (ll i=SZ(n)-1;i>=0;i--) {
    sum1 += mpow(n[i]-'0',SZ(n));
    sum2 += base*(n[i]-'0');
    base *= b;
  }

  debug(sum1);
  debug(sum2);
  if (sum1 == sum2) {
    cout << "YES" << endl;
  } else {
    cout << "NO"<< endl;
  }
  return 0;
}


