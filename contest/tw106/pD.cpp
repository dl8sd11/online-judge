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
const ll MAXN = 3000;
ll t,p,q,k;
vector<ll> edge[MAXN];
vector<ll> G[300000];
bool vis[MAXN];
bool mat[300000];
ll yp[MAXN];
bool DFS(ll x) {
  for (auto v:edge[x]) {
    if (vis[v]) continue;
    vis[v] = 1;
    if (yp[v]==-1 || DFS(yp[v])) {
      yp[v] = x;
      return true;
    }
  }
  return false;
}

ll DFS2(ll nd,ll par) {
  ll ret = 0;
  for (auto v:G[nd]) if (v != par) {
      ret += DFS2(v,nd);
      if (!mat[v] && !mat[nd]) {
	mat[nd] = true;
	ret++;
      }
    }
  return ret;
}
/*************Good*Luck******************/
int main() {
  cin >> t;
  while (t--) {
    cin >> p >> q >> k;

    if (p <= 1500) {
      REP1 (i,p) {
	edge[i].clear();
      }
    }
    

      REP1 (i,p+q) {
	G[i].clear();
      }

    REP (i,k) {
      ll u,v;
      cin >> u >> v;
      if (u <= 1500 ) {
	edge[u].emplace_back(v);
      }
      
      if (p > 1500 || q > 1500) {
	G[u].emplace_back(v+p);
	G[v+p].emplace_back(u);
      }
    }

    if (p <= 1500 && q <= 1500) {
      MEM(yp,-1);

      ll cnt = 0;
      REP1 (i,p) {
	MEM(vis,0);
	if (DFS(i)) {
	  cnt++;
	}
      }

      cout << cnt << endl;
    } else {
      MEM(mat,0);
      cout << DFS2(1,1) << endl;
    }
    
  }
  return 0;
}


