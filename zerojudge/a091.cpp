#include <bits/stdc++.h>
using namespace std;
int cmd,n;
multiset<int> s;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  auto it = s.begin();
  auto rit = s.rbegin();
  while(cin>>cmd) {
    if(cmd==1) {
      cin>>n;
      s.insert(n);
    } else if(cmd==2) {
      rit = s.rbegin();
      cout<<*rit<<endl;
      s.erase(next(rit).base());
    } else if(cmd==3) {
      it = s.begin();
      cout<<*it<<endl;
      s.erase(it);
    }
  }
}
