#include <bits/stdc++.h>
using namespace std;
int n,r,cnt,tg;
int a[10];
bool used[10];
bool solve(int idx) {
  if (idx==r) {
    if (++cnt==tg) return 1;
    else return 0;
  }
  bool ret = 0;
  for (int i=0;i<n;i++) {
    if (!idx&&!i&&r!=1)continue;
    if (used[i])continue;
    a[idx] = i;
    used[i]=1;
    ret=solve(idx+1);
    used[i]=0;
    if (ret)break;
  }
  return ret;
}
int main() {
  cin>>n>>r;
  tg = n-1;
  for(int i=1;i<r;i++) {
    tg*=n-i;
  }
  tg = tg-n-r+1;
  if (tg<0) tg = 1;
  solve(0);
  for (int i=0;i<r;i++) cout<<a[i];
}
