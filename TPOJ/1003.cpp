#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n,q,c,a,b;
ll BIT[1000003];
ll qry(ll x){
  ll ret = 0;
  for(;x>=1;x-=x&-x)ret += BIT[x];
  return ret;
}
void add(ll x,ll val){
  for(;x<=n;x+=x&-x)BIT[x] += val;
}
int main(){
  while(cin>>n>>q){
    memset(BIT,0,sizeof BIT);
    for(ll i=1;i<=n;i++)cin>>c,add(i,c);
    while(q--){
      cin>>c>>a>>b;
      if(c==0){
        add(a,b);
      }else{
        cout<<qry(b)-qry(a-1)<<endl;
      }
    }
  }
}
