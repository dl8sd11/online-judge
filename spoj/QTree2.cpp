#include <bits/stdc++.h>
using namespace std;
typedef int ll;
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

const int MAXN = 10003;
const int MAXLG = __lg(MAXN) + 3;
int T,n,a,b,c;
struct ed{
  int u,v,w,n;
}edge[MAXN*2];

int sum[MAXLG][MAXN],dep[MAXN],anc[MAXLG][MAXN];
int head[MAXN],o;

void add_edge(int u,int v,int w){
  edge[o].u =u;
  edge[o].v = v;
  edge[o].w = w;
  edge[o].n = head[u];
  head[u] = o++;
}

void dfs(int nd,int par){
  debug(nd);
  dep[nd] = dep[par] + 1;
  anc[0][nd] = par;
  for(int i=head[nd];i!=-1;i=edge[i].n){
    if(edge[i].v==par)continue;
    dfs(edge[i].v,nd);
    sum[0][edge[i].v] = edge[i].w;
  }
}
int dist(int u,int v){
  int ret = 0;
  if(dep[u]<dep[v])swap(u,v);
  for (int i=MAXLG-1;i>=0;i--) {
    if(dep[anc[i][u]]>=dep[v])ret += sum[i][u],u = anc[i][u];
  }
  if(u==v)return ret;
  for(int i=MAXLG-1;i>=0;i--){
    if(anc[i][u]!=anc[i][v]){
      ret += sum[i][u];
      ret += sum[i][v];
      u = anc[i][u];
      v = anc[i][v];
    }
  }
  return ret + sum[0][u] + sum[0][v];
}

void build_lca(){
  for(int i=1;i<MAXLG;i++){
    for(int j=1;j<=n;j++){
      anc[i][j] = anc[i-1][anc[i-1][j]];
      sum[i][j] = sum[i-1][j] + sum[i-1][anc[i-1][j]];
    }
  }
}

int get_lca(int u,int v){
  if(dep[u]<dep[v])swap(u,v);
  for (int i=MAXLG-1;i>=0;i--) {
    if(dep[anc[i][u]]>=dep[v])u = anc[i][u];
  }
  if(u==v)return u;
  for(int i=MAXLG-1;i>=0;i--){
    if(anc[i][u]!=anc[i][v]){
      u = anc[i][u];
      v = anc[i][v];
    }
  }
  return anc[0][u];
}
int kth_anc(int u,int k){
  debug(u,k);
  int goal = dep[u]-k;
  for(int i=MAXLG-1;i>=0;i--){
    if(dep[anc[i][u]]>=goal)u = anc[i][u];
  }
  return u;
}
int kth(int u,int v,int k){
  int lca =get_lca(u,v);
  if(dep[u]-dep[lca]+1<k){
    return kth_anc(v,(dep[u]+dep[v]-dep[lca]*2-(k-1)));
  } else {
    return kth_anc(u,k-1);
  }
}

int main() {
  ios_base::sync_with_stdio(0);cin.tie(0);
  cin>>T;
  while(T--){
    cin>>n;
    // memset(head,-1,n*4);
    MEM(head,-1);
    o = 0;
    REP(i,n-1) {
      cin>>a>>b>>c;
      add_edge(a,b,c);
      add_edge(b,a,c);
    }

    dfs(1,1);
    build_lca();


    string cmd;
    while(cin>>cmd&&cmd!="DONE"){
      if(cmd=="DIST"){
        cin>>a>>b;
        cout<<dist(a,b)<<endl;
      } else {
        cin>>a>>b>>c;
        cout<<kth(a,b,c)<<endl;
      }
    }
  }

}
