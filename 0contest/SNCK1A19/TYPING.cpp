#include <bits/stdc++.h>
using namespace std;

int t,n;
int ans;
string a;
map<char,bool> lr;
map <string,int> mp;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  lr['d'] = 0;
  lr['f'] = 0;
  lr['j'] = 1;
  lr['k'] = 1;
  cin>>t;
  while(t--){
    cin>>n;
    mp.clear();
    ans = 0;
    for (int i=0;i<n;i++) {
      cin>>a;
      if(mp.find(a)!=mp.end()){
        ans += mp[a]/2;
      }else{
        int delta = 0;
        delta += 2;
        for(int j=1;j<a.size();j++){
          if(lr[a[j]] == lr[a[j-1]]) delta += 4;
          else delta += 2;
        }
        mp[a] = delta;
        ans += delta;
        #ifdef tmd
          cout<<a<<" "<<delta<<endl;
        #endif
      }
    }
    cout<<ans<<endl;
  }
}
