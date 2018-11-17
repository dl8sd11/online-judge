#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


ll mymul(ll a,ll b,ll md) {
  a = a % md;
  b = b % md;
  ll ans = 0;
  while (b) {
    if (b&1) ans = (ans + a)%md;
    b >>= 1;
    a <<= 1;
    if (a > md) a -= md;
  }
  return ans;
}

ll mypow(ll base,ll ex,ll md) {
  ll ans = 1;
  while (ex) {
    if (ex&1) ans = mymul(ans,base,md);
    base = mymul(base,base,md);
    ex >>= 1;
  }
  return ans;
}

bool miller_rabin(ll vd,ll p) {
  if (p==2) return true;
  else if (p<2) return false;
  ll u = p-1,t = 0;
  while (!(u&1)) {
    u >>= 1;
    t++;
  }
  ll x = mypow(vd,u,p);
  if (x==1 || x == p-1) return true;
  for (ll i=0;i<t;i++) {
    x = mymul(x,x,p);
    if (x==1) return false;
    else if (x==p-1) return true;
  }
  return false;
}

int main () {
  cout<<mypow(2,10,1000)<<endl;
  ll p;
  cin>>p;
  ll ans = 1;
  ll vd[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};

  for (ll i=0;i<15;i++) {
    ans &= miller_rabin(vd[i],p);
  }

  if (ans) {
    cout<<"Yes"<<endl;
  } else {
    cout<<"No"<<endl;
  }
}