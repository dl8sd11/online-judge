\#include <bits/stdc++.h>
using namespace std;
int V = 100, E = 1000;

int adj[20]; // adjacency lists，初始化為-1。
struct Element {int b, r, next;} e[2005];
int en = 0;

void addedge(int a, int b, int c)
{
    e[en] = (Element){b, c, adj[a]}; adj[a] = en++;
    e[en] = (Element){a, 0, adj[b]}; adj[b] = en++;
}

int d[20];       // 最短距離
bool visit[20];  // BFS/DFS visit record
int q[20];       // queue

// 計算最短路徑，求出容許網路。
int BFS(int s, int t)
{
    memset(d, 0x7f, sizeof(d));
    memset(visit, false, sizeof(visit));

    int qn = 0;
    d[s] = 0;
    visit[s] = true;
    q[qn++] = s;

    for (int qf=0; qf<qn; ++qf)
    {
        int a = q[qf];
        for (int i = adj[a]; i != -1; i = e[i].next)
        {
            int b = e[i].b;
            if (e[i].r > 0 && !visit[b])
            {
                d[b] = d[a] + 1;
                visit[b] = true;
                q[qn++] = b;
                if (b == t) return d[t];
            }
        }
    }
    return V;
}

// 求出一條最短擴充路徑，並擴充流量。
int DFS(int a, int df, int s, int t)
{
    if (a == t) return df;

    if (visit[a]) return 0;
    visit[a] = true;

    for (int i = adj[a]; i != -1; i = e[i].next)
    {
        int b = e[i].b;
        if (e[i].r > 0 && d[a] + 1 == d[b])
        {
            int f = DFS(b, min(df, e[i].r), s, t);
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

int dinic(int s, int t)
{
    int flow = 0;
    while (BFS(s, t) < V)
        while (true)
        {
            memset(visit, false, sizeof(visit));
            int f = DFS(s, 1e9, s, t);
            if (!f) break;
            flow += f;
        }
    return flow;
}

int main(){
  int t;
  cin>>t;
  for(int caseno=1;caseno<=t;caseno++){
    memset(adj,-1,sizeof adj);
    en = 0;
    cin>>V>>E;
    int x,y,c;
    for(int i=0;i<E;i++){
      cin>>x>>y>>c;
      addedge(x,y,c);
    }
    cout<<"Case "<<caseno<<": "<<dinic(1,V)<<endl;
  }
}
