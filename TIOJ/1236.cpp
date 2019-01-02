#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll V = 100, E = 1000;
const ll MAXN = 203;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll adj[MAXN]; // adjacency lists，初始化為-1。
ll in[MAXN],out[MAXN];
struct Element {ll b, r, next;} e[40005];
ll en = 0;

void addedge(ll a, ll b, ll c)
{
    e[en] = (Element){b, c, adj[a]}; adj[a] = en++;
    e[en] = (Element){a, 0, adj[b]}; adj[b] = en++;
}

ll d[MAXN];       // 最短距離
bool visit[MAXN];  // BFS/DFS visit record
ll q[MAXN];       // queue
ll cap[MAXN];
// 計算最短路徑，求出容許網路。
ll BFS(ll s, ll t)
{
    memset(d, INF, sizeof(d));
    memset(visit, false, sizeof(visit));

    ll qn = 0;
    d[s] = 0;
    visit[s] = true;
    q[qn++] = s;

    for (ll qf=0; qf<qn; ++qf)
    {
        ll a = q[qf];
        for (ll i = adj[a]; i != -1; i = e[i].next)
        {
            ll b = e[i].b;
            if (e[i].r > 0 && !visit[b])
            {
                d[b] = d[a] + 1;
                visit[b] = true;
                q[qn++] = b;
                if (b == t) return d[t];
            }
        }
    }
    return 2*V+2;
}

// 求出一條最短擴充路徑，並擴充流量。
ll DFS(ll a, ll df, ll s, ll t)
{
    if (a == t) return df;

    if (visit[a]) return 0;
    visit[a] = true;

    for (ll i = adj[a]; i != -1; i = e[i].next)
    {
        ll b = e[i].b;
        if (e[i].r > 0 && d[a] + 1 == d[b])
        {
            ll f = DFS(b, min(df, e[i].r), s, t);
            if (f)
            {
                e[i].r -= f;
                e[i^1].r += f;
                return f;
            }
        }
    }
    return 0;
}

ll dinic(ll s, ll t)
{
    ll flow = 0;
    while (BFS(s, t) < 2*V+2)
        while (true)
        {
            memset(visit, false, sizeof(visit));
            ll f = DFS(s, INF, s, t);
            if (!f) break;
            flow += f;
            // cout<<flow<<xendl;
        }
    return flow;
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin>>V;
  memset(adj,-1,sizeof adj);
  memset(in,0,sizeof in);
  memset(out,0,sizeof out);
  for(ll i=1;i<=V;i++)cin>>cap[i],addedge(i,i+V,cap[i]);
  cin>>E;
  ll f,t;
  while(E--) {
    cin>>f>>t;
    addedge(f+V,t,INF);
    in[t]++;
    out[f]++;
  }
  for(ll i=1;i<=V;i++){
    if(!in[i]){
      addedge(0,i,INF);
    }
    if(!out[i]){
      addedge(i+V,2*V+1,INF);
    }
  }
  cout<<dinic(0,2*V+1)<<endl;

}
