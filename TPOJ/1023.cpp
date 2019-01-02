#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000009;
ll mul(ll v1,ll v2){
  return v1*v2%MOD;
}
ll add(ll v1,ll v2){
  return (v1+v2)%MOD;
}

struct M {
  ll p1,p2,p3,p4;
  M operator * (const M &a){
    return M(add(mul(p1,a.p1),mul(p2,a.p3)),add(mul(p1,a.p2),mul(p2,a.p4)),add(mul(p3,a.p1),mul(p4,a.p3)),add(mul(p3,a.p2),mul(p4,a.p4)));
  }
  M (ll i1,ll i2,ll i3,ll i4):p1(i1),p2(i2),p3(i3),p4(i4){}
};

M myExp(M base,ll ex){
  if(ex==1)return base;
  M tmp = myExp(base,ex/2);
  return (ex&1)?(tmp*tmp*base):(tmp*tmp);
}
ll t,x,y,f,g,n;
int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin>>t;
  while(t--){
    cin>>x>>y>>f>>g>>n;
    x = add(x,0);
    y = add(y,0);
    f = add(f,0);
    g = add(g,0);
    M m = M(g,f,1,0);
    if(n==1) cout<<x<<endl;
    else if (n==2) cout<<y<<endl;
    else {
      m = myExp(m,n-2);
      cout<<add(mul(y,m.p1), mul(x,m.p2))<<endl;;
    }
  }
}
