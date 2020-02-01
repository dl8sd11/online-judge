#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN = 1025;
ll BIT[MAXN][MAXN],n,cmd;
void add(ll x,ll y,ll data){for(;x<=n;x+=x&-x)for(ll i=y;i<=n;i+=i&-i)BIT[x][i]+=data;}
ll sum(ll x,ll y) {
  ll ret=0;
  for(;x>=1;x-=x&-x)for(ll i=y;i>=1;i-=i&-i)ret+=BIT[x][i];
  return ret;
}
int main(){
  cin>>n;
  ll x1,x2,y1,y2,z;
  while(cin>>cmd){
    if(cmd==1){
      cin>>x1>>y1>>z;
      x1++,y1++;
      add(x1,y1,z);
    }else{
      cin>>x1>>y1>>x2>>y2;
      x1++,y1++,x2++,y2++;
      cout<<sum(x2,y2)-sum(x1-1,y2)-sum(x2,y1-1)+sum(x1-1,y1-1)<<endl;
    }
  }
}
