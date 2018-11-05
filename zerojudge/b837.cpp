#include <bits/stdc++.h>
using namespace std;

int t,l,r;
vector<int> fab,ans;
int main() {
  ios_base::sync_with_stdio(0);cin.tie(0);
  fab.push_back(0);
  fab.push_back(1);
  while(fab[fab.size()-1] + fab[fab.size()-2] <=1000000)fab.push_back(fab[fab.size()-1] + fab[fab.size()-2]);
  cin>>t;
  while(t--){
    cin>>l>>r;
    if(l>r)swap(l,r);
    ans.clear();
    for(auto it = lower_bound(fab.begin(),fab.end(),l); it < upper_bound(fab.begin(),fab.end(),r);it++)ans.push_back(*it);
    for(auto v:ans)cout<<v<<'\n';
    cout<<ans.size()<<'\n';
    if(t)cout<<"------\n";
  }
}
