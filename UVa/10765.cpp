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

const ll MOD=1000000007;
const ll INF=0x3f3f3f3f;
const ll MAXN=1e5+5;
const ll MAXLG=__lg(MAXN)+2;

int n,m;
int x,y;
vector<int> edge[MAXN];
vector<pii> rk;
int comp,low[MAXN],dfn[MAXN],timestamp;
bool vis[MAXN];

bool cmp(const pii &a,const pii &b){
  if(a.Y!=b.Y) return a.Y>b.Y;
  else return a.X < b.X;
}
void DFS(int nd,int par){
  vis[nd] = 1;
  for(auto v:edge[nd]){
    if(v==par||vis[v])continue;
    DFS(v,nd);
  }

}

void DFS2(int nd,int par){
  low[nd] = dfn[nd] = ++timestamp;
  int compp = 0;
  int child = 0;
  for(auto v:edge[nd]){
    if(v==par)continue;
    if(!dfn[v]){
      DFS2(v,nd);
      child++;
      low[nd] = min(low[nd],low[v]);
      if(low[v]>=dfn[nd])compp++;
    } else low[nd] = min(low[nd],dfn[v]);
  }
  debug(nd,compp,comp);
  if(nd!=par) rk.pb({nd,comp+compp});
  else rk.pb({nd,comp+child-1});
}
int cnt,root[MAXN];
/********** Main()  function **********/
int main()
{
  IOS();
  while(cin>>n>>m&&(n!=0||m!=0)){
    REP(i,n)edge[i].clear();
    rk.clear();
    MEM(vis,0);
    MEM(low,0);
    MEM(dfn,0);
    timestamp = 0;
    while(cin>>x>>y&&(x!=-1&&y!=-1)){
      edge[x].pb(y);
      edge[y].pb(x);
    }
    comp = 0;
    cnt = 0;
    REP(i,n){
      if(!vis[i]){
        DFS(i,i);
        comp++;
        root[cnt++]=i;
      }
    }

    debug(comp);

    REP(i,cnt)DFS2(root[i],root[i]);

    sort(ALL(rk),cmp);
    debug(rk);
    for(int i=0;i<m;i++){
      cout<<rk[i].X<<" "<<rk[i].Y<<endl;
    }
    cout<<endl;
  }
	return 0;
}
