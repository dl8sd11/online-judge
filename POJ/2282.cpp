#include <iostream>
#include <cmath>

using namespace std;
typedef long long ll;

ll a,b;
ll cnta[10];
ll cntb[10];
ll pw[10];
ll cur,pre,suf;
void gen(){
  ll base = 1;
  for(ll i=0;i<10;i++){
    pw[i] = base;
    base *= 10;
  }
}

ll getpre(ll x,ll idx){
  return x/pw[idx+1];
}
ll getsuf(ll x,ll idx){
  return x%pw[idx];
}
ll getcur(ll x,ll idx){
  return x/pw[idx]%10;
}

void solve(ll x,ll *cnt){
  for(int i=0;i<10;i++){
    cnt[i] = 0;
  }
  if(x == -1)return;
  for(ll i=0;i<10;i++){
    for(ll j=0;j<=ll(log10(x));j++){
      cur = getcur(x,j);
      pre = getpre(x,j);
      suf = getsuf(x,j);
      if(i==0) pre-=1;
      cnt[i] += pre * pw[j];
      if (cur > i) {
	cnt[i] += pw[j];
      } else if (cur == i) {
	cnt[i] += suf + 1;
      }

    }
  }
}
int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  gen();
  for(ll i=0;i<503;i++){
    cin>>a>>b;
    if(a==0&&b==0)break;
    if(b<a)swap(a,b);
    solve(a-1,cnta);
    solve(b,cntb);
    
    for(ll j=0;j<10;j++){
      cout<<cntb[j] - cnta[j]<<" \n"[j==9];
    }

    
  }
}
