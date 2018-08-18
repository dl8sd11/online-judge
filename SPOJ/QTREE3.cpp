#include <bits/stdc++.h>
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
using namespace std;

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


const int MAXN = 100003;
struct ed{
  int u,v,n;
}e[MAXN*2];
int n,q,a,b;
int head[MAXN],cnt,dep[MAXN],top[MAXN],sz[MAXN],son[MAXN],fat[MAXN];

struct compare{
  bool operator() (const int &x,const int &y) const {
    return dep[x] < dep[y];
  }
};
vector<set<int,compare>> st;
bool color[MAXN];
int sti[MAXN];
void add_edge(int u,int v){
  e[cnt].u = u;
  e[cnt].v = v;
  e[cnt].n = head[u];
  head[u] = cnt++;
}
void dfs1(int nd,int par){
  dep[nd] = dep[par] + 1;
  sz[nd] = 1;
  son[nd] = 0;
  fat[nd] = par;
  for(int i=head[nd];i!=-1;i=e[i].n){
    if(e[i].v==par)continue;
    dfs1(e[i].v,nd);
    sz[nd] += sz[e[i].v];
    if(sz[e[i].v] > sz[son[nd]])son[nd] = e[i].v;
  }
}
void dfs2(int nd,int tp){
  top[nd] = tp;
  if(son[nd])dfs2(son[nd],tp);
  for(int i=head[nd];i!=-1;i=e[i].n){
    if(e[i].v==fat[nd]||e[i].v==son[nd])continue;
    dfs2(e[i].v,e[i].v);
  }
}
void change(int v){
  color[v] = !color[v];
  if(color[v]){
    st[sti[top[v]]].insert(v);
  } else {
    st[sti[top[v]]].erase(v);
  }
}

int query(int v){
  int ft = -1;
  if(color[1])return 1;
  while(v!=1){
    int st_idx = sti[top[v]];
    if(st[st_idx].size()){
        int tmp = *st[st_idx].begin();
        if(dep[tmp] <= dep[v]) ft = tmp;
    }
    v = fat[top[v]];
  }

  return ft;
}

int main(){

  cin>>n>>q;
    memset(head,-1,sizeof head);
    memset(color,0,sizeof color);
    REP(i,n-1){
      cin>>a>>b;
      add_edge(a,b);
      add_edge(b,a);
    }

    dfs1(1,1);
    dfs2(1,1);

    st.clear();
    REP1(i,n)if(top[i]==i){
      st.emplace_back();
      sti[i] = st.size()-1;
    }

    int cmd,v;
    while(q--){
      cin>>cmd>>v;
      if(cmd==1){
        cout<<query(v)<<endl;
      }else {
        change(v);
      }
    }


}
