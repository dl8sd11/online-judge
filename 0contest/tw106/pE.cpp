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
const ll MAXN = 5007;

ll n,m;
vector<ll> edge[MAXN];
ll djs[MAXN];
ll sz[MAXN];
bool vis[MAXN];
ll deg[MAXN];
void init() {
  REP1 (i,n) {
    djs[i] = i;
    sz[i] = 1;
  }
}

ll fnd(ll x) {
  return x==djs[x] ? x: djs[x] = fnd(djs[x]);
}

void uni(ll x,ll y) {
  if (sz[x=fnd(x)] > sz[y=fnd(y)]) {
    swap(x,y);
  }
  djs[x] = y;
  sz[y] += sz[x];
}

int getint()
{
    int ans=0, tmp;
    while( (tmp=getchar()) && (tmp<'0' || tmp>'9') );
    
    do{
        ans=(ans<<3)+(ans<<1)+(tmp-'0');
    }while( (tmp=getchar()) && ('0'<=tmp && tmp<='9') );
    
    return ans;
}

/*************Good*Luck******************/
int main() {
  n = getint();
  m = getint();
  REP (i,m) {
    ll u = getint();
    ll v = getint();
    edge[u].emplace_back(v);
    edge[v].emplace_back(u);
  }

  REP1 (i,n) {
    deg[i] = SZ(edge[i]);
  }

  vector<pair<ll,ll> > Q;
  while(true) {
    ll s = INF;
    REP1 (i,n) {
      if (!vis[i]) {
        s = min(s,deg[i]);
      }
    }

    if (s == INF) {
      break;
    }

    queue<ll> BFS;
    REP1 (i,n) {
      if (!vis[i] && deg[i]==s) {
        BFS.push(i);
        vis[i] = true;
      }
    }

    while (BFS.size()){
      ll cur = BFS.front();BFS.pop();
      Q.emplace_back(cur,s);
      for (auto v:edge[cur]) {
        if (!vis[v] && --deg[v] <= s) {
          BFS.emplace(v);
          vis[v] = true;
        }
      }
    }
  }

  init();
  ll ans = 0;
  for (ll i=SZ(Q)-1;i>=0;i--) {
    vis[Q[i].X] = 0;
    for (auto v:edge[Q[i].X]) {
      if (!vis[v]) {
        if (fnd(Q[i].X) != fnd(v)) {
          uni(Q[i].X,v);
        }
        ans = max(ans,sz[fnd(v)]*Q[i].Y);
      }
    }
  }

  printf("%d\n",ans);
  return 0;
}


