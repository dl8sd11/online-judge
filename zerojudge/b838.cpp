#include <bits/stdc++.h>
using namespace std;

int t;
string par;
int ans;
vector<bool> sk;
int main() {
  cin>>t;
  cin.ignore();
  while(t--){
    sk.clear();
    ans = 0;
    getline(cin,par);
    for(int i=0;i<int(par.size());i++){
      if(par[i] == '(')sk.emplace_back(0);
      else if(par[i] == ')'){
        if(sk.size())sk.pop_back(),ans++;
        else {
          ans = 0;
          break;
        }
      }
    }
    if(sk.size())cout<<0<<endl;
    else cout<<ans<<endl;
  }
}
