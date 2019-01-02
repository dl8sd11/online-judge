#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1000003;
ll t[MAXN*2];
ll n,q,a,b,c;

void build(){
  for(ll i=n-1;i>0;i--)t[i] = t[i<<1]+t[i<<1|1];
}
void add(ll x,ll y){
  for(t[x+=n]+=y;x>1;x>>=1)t[x>>1] = t[x] + t[x^1];
}
ll query(ll l,ll r){
  ll res = 0;
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1)res+=t[l++];
    if(r&1)res+=t[--r];
  }
  return res;
}
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  cin>>n;
  cin>>q;
  for(int i=0;i<n;i++)cin>>t[i+n];
  build();
  while(q--){
    cin>>c>>a>>b;
    --a;
    if(c==0){
      add(a,b);
    } else {
      cout<<query(a,b)<<endl;
    }
  }
}
