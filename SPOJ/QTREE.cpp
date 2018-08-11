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
// #define max(i,j) ((i)>(j)?(i):(j))
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

struct edge{
  int u,v,w,n;
}e[MAXN*2];

int t,n,a,b,c;
int dep[MAXN],sz[MAXN],fat[MAXN],son[MAXN],top[MAXN];
int in[MAXN],cnt,idx,head[MAXN];
int sg[MAXN*2];
char cmd[10];

void add_edge(int u,int v,int w){
  e[cnt].u = u;
  e[cnt].v = v;
  e[cnt].w = w;
  e[cnt].n = head[u];
  head[u] = cnt++;
}

void build_seg () {
  for (int i=n-1;i>0;i--) {
    sg[i] = max(sg[i<<1],sg[i<<1|1]);
  }
}

void modi (int x,int y) {

  for (sg[x+=n]=y;x>1;x>>=1) {
    sg[x>>1] = max(sg[x],sg[x^1]);
  }
}

int query (int l,int r) {
  debug(l,r);
  int res = 0;
  for (l+=n,r+=n;l<r;l>>=1,r>>=1) {
    // debug(l,r);
    if(l&1)res = max(res,sg[l++]); //max(res,sg[l--]);
    if(r&1)res = max(res,sg[--r]);
  }
  return res;
}

void dfs1 (int nd,int par) {
  dep[nd] = dep[par] + 1;
  sz[nd] = 1;
  fat[nd] = par;
  son[nd] = 0;
  for (int i=head[nd];i!=-1;i=e[i].n) {
    if (e[i].v==par) continue;
    dfs1(e[i].v,nd);
    sz[nd] += sz[e[i].v];
    if(sz[e[i].v] > sz[son[nd]]) son[nd] = e[i].v;
  }
}

void dfs2 (int nd,int tp) {
  in[nd] = idx++;
  top[nd] = tp;
  if (son[nd]) dfs2(son[nd],tp);
  for (int i=head[nd];i!=-1;i=e[i].n) {
    if (e[i].v==fat[nd] || e[i].v==son[nd]) continue;
    dfs2(e[i].v,e[i].v);
  }
}

int qpath (int x,int y) {
  int ret = 0;
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) swap(x,y);
    debug(in[top[x]],in[x]+1);
    ret = max(ret,query(in[top[x]],in[x]+1));
    x = fat[top[x]];
  }
  if(x==y)return ret;
  if (dep[x] < dep[y]) swap(x,y);
  debug(in[son[y]],in[x]+1);
  ret = max(ret,query(in[son[y]],in[x]+1));
  return ret;
}

int main(){
  IOS();
  cin>>t;
  while(t--){
    cin>>n;

    memset(head,-1,sizeof head);
    cnt = 0;
    REP(i,n-1){
      cin>>a>>b>>c;
      add_edge(a,b,c);
      add_edge(b,a,c);
    }
    idx = 0;
    dep[0] = -1;
    dfs1(1,1);
    dfs2(1,1);

    for (int i=0;i<cnt;i+=2) {
      if (dep[e[i].u] < dep[e[i].v]) swap(e[i].u,e[i].v);
      sg[n+in[e[i].u]] = e[i].w;
    }

    build_seg();

    pary(sg+n,sg+2*n);
    pary(in+1,in+n+1);

    while (cin>>cmd&&cmd[0]!='D') {
      cin>>a>>b;
      if (cmd[0]=='Q') {
        cout<<qpath(a,b)<<endl;
      } else {
        modi(in[e[(a-1)*2].u],b);
      }
    }
    // cout<<endl;
  }
}
