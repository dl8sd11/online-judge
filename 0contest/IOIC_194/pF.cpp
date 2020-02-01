#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) ll(i.size())
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
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
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

template<class T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template<class T> using MaxHeap = priority_queue<T>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

const ll MOD=1000000007;
const ll MAXN=2003;
const ll MAXLG=__lg(MAXN)+2;


#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

const long long INF = 0x3f3f3f3f3f3f3f3f;

vector<ll> ans;
struct graph {
  typedef long long flow_type;
  struct edge {
    int src, dst;
    flow_type capacity, flow;
    size_t rev;
  };
  int n;
  vector<vector<edge>> adj;
  graph(int n) : n(n), adj(n) { }
    void dfs_cut(ll nd,ll par) {
        ans.emplace_back(nd);
        for (auto e:adj[nd]) {
            if (e.capacity != 0 && e.dst != par && e.flow < e.capacity) {
                debug(e.src,e.dst,e.capacity,e.flow);
                dfs_cut(e.dst,nd);
            }
        }
    }

  void add_edge(int src, int dst, flow_type capacity) {
    adj[src].push_back({src, dst, capacity, 0, adj[dst].size()});
    adj[dst].push_back({dst, src, 0, 0, adj[src].size()-1});
  }
  flow_type max_flow(int s, int t) {
    vector<int> level(n), iter(n);
    function<int(void)> levelize = [&]() { // foward levelize
      level.assign(n, -1); level[s] = 0;
      queue<int> Q; Q.push(s);
      while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        if (u == t) break;
        for (auto &e: adj[u]) {
          if (e.capacity > e.flow && level[e.dst] < 0) {
            Q.push(e.dst);
            level[e.dst] = level[u] + 1;
          }
        }
      }
      return level[t];
    };
    function<flow_type(int, flow_type)> augment = [&](int u, flow_type cur) {
      if (u == t) return cur;
      for (int &i = iter[u]; i < adj[u].size(); ++i) {
        edge &e = adj[u][i], &r = adj[e.dst][e.rev];
        if (e.capacity > e.flow && level[u] < level[e.dst]) {
          flow_type f = augment(e.dst, min(cur, e.capacity - e.flow));
          if (f > 0) {
            e.flow += f;
            r.flow -= f;
            return f;
          }
        }
      }
      return flow_type(0);
    };
    for (int u = 0; u < n; ++u) // initialize
      for (auto &e: adj[u]) e.flow = 0;

    flow_type flow = 0;
    while (levelize() >= 0) {
      fill(all(iter), 0);
      for (flow_type f; (f = augment(s, INF)) > 0; )
        flow += f;
    }
    return flow;
  }
};


/********** Good Luck :) **********/
int main()
{
    IOS();
    ll t,n,m;
    cin >> t;
    while (t--) {
        vector<ll> inp[MAXN];
        cin >> m >> n;
        graph g(n+m+2);
        ll sum = 0;
        REP (i,m) {
            ll c;
            cin >> c;
            g.add_edge(n+i+1,n+m+1,c);
        }
        REP (i,n) {
            ll ni,p;
            cin >> ni >> p;
            sum += p;
            g.add_edge(0,i+1,p);
            REP (j,ni) {
                ll d;
                cin >> d;
                inp[i+1].emplace_back(d);
                g.add_edge(i+1,n+d,INF);
            }
        }

        cout << sum - g.max_flow(0,n+m+1) << endl;
        
        ans.clear();
        g.dfs_cut(0,0);

        set<ll> st;
        for (auto e:ans) {
            debug(e);
            if (e < 1 || e > n) {
                continue;
            }
            for (auto d:inp[e]) {
                st.insert(d);
            }
        }

        cout << st.size() << endl;
        for (auto s : st) {
            cout << s <<  " ";
        }
        cout << endl;

    }

    return 0;
}