#include <iostream>
#include <string>
using namespace std;

int cur,ans;
string s;
int main(){
  cin>>s;
  for(int i=0;i<=int(s.size());i++){
    if(s[i]!='F'){
      ans = max(ans,cur);
      cur = 0;
    } else {
      cur++;
    }
  }
  cout<<ans<<endl;
}
