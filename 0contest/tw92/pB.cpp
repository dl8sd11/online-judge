#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define SZ(i) ll(i.size())
#ifdef tmd
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
#define IOS()
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#define endl '\n'
#endif

ll ans = 0;
string tmp;
int main () {
  while(cin >> tmp) {
    bool flag = 0;
    REP (i,SZ(tmp)) {
      if (tmp[i] >= 'a' && tmp[i] <= 'z') {
        flag = true;
      }
      if (tmp[i] >= 'A' && tmp[i] <= 'Z') {
        flag = true;
      }
      if (tmp[i] >= '0' && tmp[i] <= '9') {
        flag = true;
      }
    }
    if (flag) {
      ans++;
    }
  }
  cout << ans << endl;
  return 0;
}