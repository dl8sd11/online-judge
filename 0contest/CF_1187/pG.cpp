#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#ifdef tmd
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<" ,";_do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s,const pair<_a,_b> &_p){return _s<<"("<<_p.X<<","<<_p.Y<<")";}
template<typename It> ostream& _OUTC(ostream &_s,It _ita,It _itb)
{
    _s<<"{";
    for(It _it=_ita;_it!=_itb;_it++)
    {
        _s<<(_it==_ita?"":",")<<*_it;
    }
    _s<<"}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s,vector<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,set<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif
#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())
#define TEST(s) if (!(s)) { cout << __LINE__ << " " << #s << endl; exit(-1); }

const ll MOD = 1000000007;
const int iNF = 0x3f3f3f3f;
const long long INF = 99999999;
// const ll MAXN = 


struct graph {
  typedef int flow_type;
  typedef int cost_type;
  struct edge {
    int src, dst;
    flow_type capacity, flow;
    cost_type cost;
    size_t rev;
  };
  vector<edge> edges;
  void add_edge(int src, int dst, flow_type cap, cost_type cost) {
    adj[src].push_back({src, dst, cap, 0, cost, adj[dst].size()});
    adj[dst].push_back({dst, src, 0, 0, -cost, adj[src].size()-1});
  }
  int n;
  vector<vector<edge>> adj;
  graph(int n) : n(n), adj(n) { }

  pair<flow_type, cost_type> min_cost_max_flow(int s, int t) {
    flow_type flow = 0;
    cost_type cost = 0;

    for (int u = 0; u < n; ++u) // initialize
      for (auto &e: adj[u]) e.flow = 0;

    vector<cost_type> p(n, 0);

    auto rcost = [&](edge e) { return e.cost + p[e.src] - p[e.dst]; };
    for (int iter = 0; ; ++iter) {
      vector<int> prev(n, -1); prev[s] = 0;
      vector<cost_type> dist(n, INF); dist[s] = 0;
      if (iter == 0) { // use Bellman-Ford to remove negative cost edges
        vector<int> count(n); count[s] = 1;
        queue<int> que; 
        for (que.push(s); !que.empty(); ) {
          int u = que.front(); que.pop();
          count[u] = -count[u];
          for (auto &e: adj[u]) {
            if (e.capacity > e.flow && dist[e.dst] > dist[e.src] + rcost(e)) {
              dist[e.dst] = dist[e.src] + rcost(e);
              prev[e.dst] = e.rev;
              if (count[e.dst] <= 0) {
                count[e.dst] = -count[e.dst] + 1;
                que.push(e.dst);
              }
            }
          }
        }
      } else { // use Dijkstra 
        typedef pair<cost_type, int> node;
        priority_queue<node, vector<node>, greater<node>> que;
        que.push({0, s});
        while (!que.empty()) {
          node a = que.top(); que.pop();
          if (a.snd == t) break;
          if (dist[a.snd] > a.fst) continue;
          for (auto e: adj[a.snd]) {
            if (e.capacity > e.flow && dist[e.dst] > a.fst + rcost(e)) {
              dist[e.dst] = dist[e.src] + rcost(e);
              prev[e.dst] = e.rev;
              que.push({dist[e.dst], e.dst});
            }
          }
        }
      }
      if (prev[t] == -1) break;

      for (int u = 0; u < n; ++u) 
        if (dist[u] < dist[t]) p[u] += dist[u] - dist[t];

      function<flow_type(int,flow_type)> augment = [&](int u, flow_type cur) {
        if (u == s) return cur;
        edge &r = adj[u][prev[u]], &e = adj[r.dst][r.rev];
        flow_type f = augment(e.src, min(e.capacity - e.flow, cur));
        e.flow += f; r.flow -= f;
        return f;
      };
      flow_type f = augment(t, INF);
      flow += f;
      cost += f * (p[t] - p[s]);
    }
    return {flow, cost};
  }
};

int n, m, k, c, d;

const int layers = 120;
vector<pair<int,int> > edge;
int main() {
    IOS();
    cin >> n >> m >> k >> c >> d;
    int s = 0, t = layers * n + 1;
    graph g(layers * n + 2);
    REP (i, k) {
        int x;
        cin >> x;
        g.add_edge(s, x, 1, 0);
    }
    REP (i,m) {
        ll u,v;
        cin >> u >> v;
        edge.eb(u,v);
    }

    REP1 (i, layers-1) {
        REP1 (j, n) {
            g.add_edge((i-1)*n+j, i*n+j, 100, c);
        }
        for (auto p : edge) {
            REP1 (j,50) {
                g.add_edge((i-1)*n+p.X,i*n+p.Y,1,d*(j*j-(j-1)*(j-1))+c);
                g.add_edge((i-1)*n+p.Y,i*n+p.X,1,d*(j*j-(j-1)*(j-1))+c);
            }
        }
    }

    REP (i,layers) {
        g.add_edge(i*n+1,t,100,0);
    }

    cout << g.min_cost_max_flow(s,t).Y << endl;
}