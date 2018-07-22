#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN = 200003;
struct seg{
  int l,r,lc,rc;
  ll data;
}nd[MAXN*4];
void pull(ll idx){
  if(nd[idx].lc!=-1)nd[idx].data = min(nd[nd[idx].lc].data,nd[nd[idx].rc].data);
}
void init(int idx,int li,int ri,int lci,int rci,ll datai){
  nd[idx].l = li;
  nd[idx].r = ri;
  nd[idx].lc = lci;
  nd[idx].rc = rci;
  nd[idx].data = datai;
}
int stptr = 0;
int n,m;
ll a[MAXN];
void build(int l,int r,int idx){
  if(r==l+1) {
    init(idx,l,r,-1,-1,a[l]);
    return;
  }
  int mid = (l+r)/2;
  int lc = ++stptr;
  int rc = ++stptr;
  build(l,mid,lc);
  build(mid,r,rc);
  init(idx,l,r,lc,rc,0LL);
  pull(idx);
  return;
}
ll qry(int l,int r,int idx){
  if(nd[idx].r==r&&l==nd[idx].l)return nd[idx].data;
  int mid = (nd[idx].l+nd[idx].r)/2;
  if(l>=mid)return qry(l,r,nd[idx].rc);
  else if(r<=mid)return qry(l,r,nd[idx].lc);
  return min(qry(l,mid,nd[idx].lc),qry(mid,r,nd[idx].rc));
}
void modi(int p,int val,int idx){
  if(nd[idx].r==nd[idx].l+1){
    nd[idx].data = val;
    return;
  }
  int mid = (nd[idx].l+nd[idx].r)/2;
  if(p>=mid) modi(p,val,nd[idx].rc);
  else if(p<mid) modi(p,val,nd[idx].lc);
  pull(idx);
}
int main(){
  ios_base::sync_sith_stdio(0);
  cin.tie(0);
  while(cin>>n>>m){
    for(int i=0;i<n;i++)cin>>a[i];
    build(0,n,0);
    char C;
    int x,y;
    while(m--){
      cin>>C>>x>>y;
      if(C=='M'){
        modi(x,y,0);
      }else{
        cout<<qry(x,y,0)<<endl;
      }
    }
  }

}
