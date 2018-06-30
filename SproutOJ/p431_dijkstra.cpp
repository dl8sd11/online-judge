#include <bits/stdc++.h>
  using namespace std;
  typedef long long ll;
  typedef pair<ll,ll> pii;
  #define MEM(a, b) memset(a, (b), sizeof(a))
  #define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
  #define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
  #define REP(i, j) FOR(i, 0, j, 1)
  #define REP1(i,j) FOR(i, 1, j+1, 1)
  #define RREP(i, j) RFOR(i, j, 0, 1)
  #define ALL(_a) _a.begin(),_a.end()
  #define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
  #define mp make_pair
  #define pb push_back
  #define X first
  #define Y second
  typedef pair<ll, ll> pi;
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

  const ll INF = (ll)1e18 + 7;
  const ll MOD = 1000000007;
  const ll MAXN = 3e5;

  vector<pii> e[MAXN];
  vector<pii> re[MAXN];


  ll n,m,Q;

  vector<ll> dijkstra(ll st,vector<pii> (&edge)[MAXN]){
    priority_queue<pii,vector<pii>,greater<pii> > pq;

    vector<ll> ret(n+5,INF);
    vector<bool> vis(n+5,0);

    ret[st] = 0;
    pq.push({0,st});

    REP(i,n){
      while(!pq.empty()&&vis[pq.top().Y])pq.pop();
      if(pq.empty())break;
      pii now = pq.top();
      vis[now.Y] = 1;
      for(auto v:edge[now.Y]){
        if(ret[v.X]>ret[now.Y] + v.Y){
          ret[v.X] = ret[now.Y] + v.Y;
          pq.push({ret[v.X],v.X});
        }
      }
    }
    return ret;
  }
  int main()
  {
    IOS();
    cin>>n>>m>>Q;
    REP(i,m){
      ll from,to,dist;
      cin>>from>>to>>dist;
      e[from].pb({to,dist});
      re[to].pb({from,dist});

    }

    vector<ll> d(n+5,INF);
    vector<ll> rd(n+5,INF);

    d = dijkstra(1,e);
    rd = dijkstra(n,re);



    REP(i,Q){
      ll from,to;
      cin>>from>>to;
      cout<<min(d[n],d[from]+1+rd[to])<<endl;
    }
  	return 0;
  }
