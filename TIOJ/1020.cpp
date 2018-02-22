#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(ll i=0;i<n;i++)
int n;
//int mx[32];
int cnt;
list<int> li,ans;
void dfs(int idx) {
  if (idx>n) {
    if (li>ans) ans = li;
    cnt++;
    return;
  }
  for (auto it = li.begin();;it++) {
    auto nx = it;
    if (++nx==li.end())break;
    if (idx%(*it+*nx)==0) {
      nx = li.insert(nx,idx);
      dfs(idx+1);
      li.erase(nx);
    }
  }
}
int main(){
  cin>>n;
  li.push_back(0);
  li.push_back(1);
  dfs(2);
  cout<<cnt<<endl;
  for(auto it:ans) cout<<it<<((it!=1)?' ':'\n');
  return 0;
}
