#include <bits/stdc++.h>
using namespace std;
// 0 1 2 3 4 5
string a;
int SZ;
int ans = -1;
bool solve1(int len,int idx){
  if(idx -len < 0 || idx +len >= SZ)return false;
  for(int i=1;i<=len;i++)if(a[idx+i] != a[idx-i])return false;
  return true;
}

bool solve2(int len,int idx){
  if(idx+1 - len < 0 || idx+len >= SZ)return false;
  for(int i=1;i<=len;i++)if(a[idx-i+1] != a[idx+i])return false;
  return true;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin>>a;
  SZ = a.size();
  assert(SZ <= 100000);
  for(int i=0;i<SZ;i++){
    int L = 0, R = SZ + 1;
    while(L < R - 1){
      int mid = (L+R)/2;
      if(solve1(mid,i))L = mid;
      else R = mid;
    }
    ans = max(L*2+1,ans);

    L = 0, R = SZ + 1;
    while(L < R - 1){
      int mid = (L+R)/2;
      if(solve2(mid,i))L = mid;
      else R = mid;
    }
    ans = max(L*2,ans);
  }

  cout<<ans<<endl;
}
