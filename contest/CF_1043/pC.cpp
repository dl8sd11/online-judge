#include <bits/stdc++.h>
using namespace std;
string s;
int main() {
  ios_base::sync_with_stdio(0);cin.tie(0);
  cin>>s;
  for(int i=1;i<int(s.size());i++){
    if(s[i]!=s[i-1]){
      for(int j=0;j<i/2;j++)swap(s[j],s[i-1-j]);
      cout<<1<<" ";
    } else {
      cout<<0<<" ";
    }
  }
  cout<<(s[0]=='b')<<endl;
}
