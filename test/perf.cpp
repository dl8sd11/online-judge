#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for (ll i=0;i<n;i++)
#define REP1(i,n)  for (ll i=1;i<=n;i++)
#define SZ(i) ll(i.size())
#define MEM(i,n) memset(i,(n),sizeof(i))
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll MAXN = 1e5+5;

ll n,m;
ll W[MAXN];

struct EDGE {
  ll u,v,w;
};
vector<EDGE> G;

struct E {
  ll t,cap,flow,prev;
};
vector<E> edge;
ll head[MAXN];

ll lev[MAXN],vis[MAXN];
void add_edge(ll f,ll t,ll cap) {
  edge.push_back((E){t,cap,0,head[f]});
  head[f] = SZ(edge) - 1;
  edge.push_back((E){f,0,0,head[t]});
  head[t] = SZ(edge) - 1; 
}

bool BFS(ll s,ll t) {
  MEM(lev,-1);
  queue<ll> q;
  q.push(s);
  lev[s] = 0;
  while (q.size()) {
    ll cur = q.front();q.pop();

    if (cur == t) {
      return true;
    }

    for (ll i=head[cur];i!=-1;i=edge[i].prev) {
      ll x = edge[i].t;
      if (lev[x] == -1 && edge[i].cap > edge[i].flow) {
        lev[x] = lev[cur] + 1;
        q.push(x);
      }
    }
  }
  return false;
}

ll DFS(ll s,ll t,ll nd,ll lim) {
  if (nd == t || lim == 0) return lim;
  for (ll i=head[nd];i!=-1;i=edge[i].prev) {
    ll x = edge[i].t;
    if (edge[i].cap > edge[i].flow && lev[x] == lev[nd] + 1) {
      ll df = DFS(s,t,x,min(lim,edge[i].cap-edge[i].flow));
      if (df) {
        edge[i].flow += df;
        edge[i^1].flow -= df;
        return df;
      }
    }
  }
  return 0;
}

ll Dinic(ll s,ll t) {
  ll flow = 0;
  while (BFS(s,t)) {
    ll df;
    while (df = DFS(s,t,s,INF)) {
      flow += df;
    }
  }
  return flow;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m;
  REP1 (i,n) {
    cin >> W[i];
  }

  ll sum = 0;
  REP (i,m) {
    ll u,v,w;
    cin >> u >> v >> w;
    sum += w;
    G.push_back((EDGE){u,v,w});
  }

  MEM(head,-1);
  REP1 (i,SZ(G)) {
    add_edge(0,i,G[i-1].w);
    add_edge(i,SZ(G)+G[i-1].u,INF);
    add_edge(i,SZ(G)+G[i-1].v,INF);
  }

  REP1 (i,n) {
    add_edge(SZ(G)+i,n+m+2,W[i]);
  }

  ll flow = Dinic(0,n+m+2);
  cout << sum - flow << endl;

  return 0;
}