#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define SZ(m) ll(m.size())
#define eb emplace_back
#define MEM(i,n) memset(i,n,sizeof(i))
#ifdef tmd
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
#define IOS()
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#define endl '\n'
#endif


const ll MAXN = 100;
string m,a;
map<char,ll> mpp;
vector<char> nd;
ll root;
ll l[MAXN],r[MAXN];
void push(ll v,char c) {
  if (mpp[nd[v]] > mpp[c]) {
    if (l[v] == -1) {
      nd.eb(c);
      l[v] = nd.size()-1;;
    } else {
      push(l[v],c);
    }
  } else {
    if (r[v] == -1) {
      nd.eb(c);
      r[v] = nd.size()-1;;
    } else {
      push(r[v],c);
    }
  }
}

void ptree(ll v) {
  if (v==-1) {
    return;
  }
  cout << nd[v];
  ptree(l[v]);
  ptree(r[v]);
}
int main () {
  MEM(l,-1);
  MEM(r,-1);
  cin >> m >> a;
  REP (i,SZ(m)) {
    mpp[m[i]] = i;
  }

  nd.eb(a.back());
  root = 0;
  for (ll i=SZ(a)-2;i>=0;i--) {
    push(root,a[i]);
  }

  ptree(root);
  cout << endl;
  return 0;
}