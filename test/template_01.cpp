#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define MEM(i,n) memset(i,(n),sizeof(i))
#define SZ(i) ll(i.size())
#define ALL(i) i.begin(),i.end()
#define eb emplace_back()
#define pb push_back()
#define X first
#define Y scond
#ifdef tmd
#define debug(...) do{fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);}while(0);
template <typename T> void _do(T &&_x){cerr<<_x<<endl;}
template <typename T,typename ...S> void _do(T &&head,S &&...tail){cerr<<head<<", ";_do(tail...);}
#define IOS()
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#define endl '\n'
#endif

int main() {
  debug(3,4);
}