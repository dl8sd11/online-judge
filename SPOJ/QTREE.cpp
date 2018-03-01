#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
#define REP(i,n) for(int i=0;i<n;i++)
#define MEM(i,n) memset(i,n,sizeof(n))
#define X first
#define Y second
#define pb push_back
#ifdef tmd
#define debug(...) do{\
  fprintf(stderr,"%s - %d : (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
  _do(__VA_ARGS__);\
}while(0)
template<typename t> void _do(t &&x){cerr<<x<<endl;}
template<typename t,typename ...T> void _do(t &&x,T &&...tail){cerr<<x<<", ";_do(tail...);}
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#endif
struct eg{
  ll x1,x2,x3;
  eg(ll a,ll b,ll c):x1(a),x2(b),x3(c){}
};
struct node{
  ll l,r;
  node *lc,*rc;
  ll data;
  void pull(){data = max(lc->data,rc->data);}
  node(ll li,ll ri,node *lci,node *rci,ll datai):l(li),r(ri),lc(lci),rc(rci),data(datai){}
};
const ll MAXN = 1003;
ll n,t,tm;
ll par[MAXN],d[MAXN],w[MAXN],mc[MAXN],tin[MAXN],h[MAXN];
vector<pii> edge[MAXN];
vector<eg> inputE;
node *root;

node *buildST(ll l,ll r) {
  if(r-l==1)return new node(l,r,0,0,0);
  ll mid = (l+r)/2;
  return new node(l,r,buildST(l,mid),buildST(mid,r),0);
}
void mody(ll l,ll r,node *nd,ll data){
  if(l==nd->l&&r==nd->r) {nd->data = data;return;}
  ll mid = (nd->l+nd->r)/2;
  if(l>=mid)mody(l,r,nd->rc,data);
  else if(r<=mid)mody(l,r,nd->lc,data);
  nd->pull();
}
ll query(ll l,ll r,node *nd) {
  //if(l==nd->l&&r==nd->r) debug(l,r,nd->data);
  if(l==nd->l&&r==nd->r) return nd->data;
  ll mid = (nd->l+nd->r)/2;
  if(l>=mid)return query(l,r,nd->rc);
  else if(r<=mid)return query(l,r,nd->lc);
  return max(query(l,mid,nd->lc),query(mid,r,nd->rc));
}
void DFS(ll idx,ll p) {
  tin[idx]=t++;
  if(idx==mc[p])h[idx]=h[p];
  else h[idx]=idx;
  if(w[idx]==1)return;
  DFS(mc[idx],idx);
  for(auto v:edge[idx]) {
    if(v.X==p||v.X==mc[idx])continue;
    DFS(v.X,idx);
  }
}
void buildTree(ll idx, ll p){
  par[idx] = p;
  d[idx]=d[p]+1;
  ll mxid = 0;
  w[idx]=1;
  for(auto v:edge[idx]) {
    if(v.X==p)continue;
    buildTree(v.X,idx);
    if(w[v.X]>w[mxid])mxid = v.X;
    w[idx]+=w[v.X];
  }
  mc[idx]=mxid;
}

int main(){
  ll T;
  cin>>T;
  while(T--) {
    debug(T);
      cin>>n;
      ll a,c,b;

      REP(i,n-1) {
        cin>>a>>b>>c;
        edge[a].pb({b,c});
        edge[b].pb({a,c});
        inputE.pb(eg{a,b,c});
      }
      d[1]=-1;
      buildTree(1,1);
      DFS(1,1);
      root =buildST(0,n);
      debug(root);

      for(auto E:inputE){
        if(par[E.x2]==E.x1) mody(tin[E.x2],tin[E.x2]+1,root,E.x3);
        else mody(tin[E.x1],tin[E.x1]+1,root,E.x3);

      }

      string cmd;
      while(cin>>cmd) {
        if(cmd=="DONE")break;
        debug(cmd);
        cin>>a>>b;
        if(cmd== "QUERY") {
          ll ret = 0;
          while(h[a]!=h[b]) {
            debug(a,b);
            if(d[a]>d[b]) {
              ret = max(ret,query(tin[h[a]]+1,tin[a]+1,root));
              a = par[h[a]];
            } else {
              ret = max(ret,query(tin[h[b]]+1,tin[b]+1,root));
              b = par[h[b]];
            }
          }
          if(d[a]<d[b]) {
            ret = max(ret,query(tin[a]+1,tin[b]+1,root));
          } else {
            ret = max(ret,query(tin[b]+1,tin[a]+1,root));
          }
          cout<<ret<<endl;
        }else {
          eg E = inputE[a];
          if(par[E.x2]==E.x1) mody(tin[E.x1],tin[E.x1]+1,root,b);
          else mody(tin[E.x2],tin[E.x2]+1,root,b);
        }
      }
  }

}
