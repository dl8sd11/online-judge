 #include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MAXN = 200003;
const ll INF = 0x3f3f3f3f3f3f3f3f;
ll q,n;
ll mn[MAXN*2];
ll mx[MAXN*2];
void build(){
  for(ll i=n-1;i>0;i--){
    mn[i] = min(mn[i<<1],mn[i<<1|1]);
    mx[i] = max(mx[i<<1],mx[i<<1|1]);
  }
}

ll query(ll l,ll r){
  ll rmx = -INF,rmn = INF;
  for(l+=n,r+=n;l<r;l>>=1,r>>=1){
    if(l&1){
      rmx = max(rmx,mx[l]);
      rmn = min(rmn,mn[l++]);
    }
    if(r&1){
      rmx = max(rmx,mx[--r]);
      rmn = min(rmn,mn[r]);
    }
  }
  return rmx - rmn;
}
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  cin>>n>>q;
  for(ll i=0;i<n;i++){
    cin>>mn[n+i];
    mx[n+i] = mn[i+n];
  }

  build();
  ll l,r;
  while(q--){
    cin>>l>>r;
    cout<<query(l-1,r)<<endl;
  }
}
