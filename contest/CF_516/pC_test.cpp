#include <bits/stdc++.h>
using namespace std;

int ans;
string test;
bool check (int l,int r) {
  while(l < r){
    if(test[l]!=test[r]) return false;
    l++,r--;
  }
  return true;
}
int main() {
  while(cin>>test){
    ans = 0;
    for(int i=0;i<test.size();i++){
      for(int j=i;j<test.size();j++){
        if(check(i,j)){
          ans++;
        }
      }
    }
    cout<<ans<<endl;
  }

}
