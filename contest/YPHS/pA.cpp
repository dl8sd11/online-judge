#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t,a,b,c;
ll f(ll x){
  return x*x*x + a*x*x + b*x +c;
}
int main(){
  cin>>t;
  while(t--){
    cin>>a>>b>>c;
    vector<ll> ans;

    for(ll i=100000;i>=-100000;i--){
      if(f(i)==0)ans.push_back(-i);
    }


    if(ans.size()==1){
      ans.push_back(ans[0]);
      ans.push_back(ans[0]);
    } else if(ans.size()==2){
      if(c==0){
        if(b==0){
          ans.push_back(0);
        }else{
          if(ans[0]==0)ans.push_back(ans[1]);
          else ans.push_back(ans[0]);
        }
      } else {
        ans.push_back(c/ans[0]/ans[1]);
      }
      sort(ans.begin(),ans.end());
    }

    for(ll i=0;i<3;i++){
      cout<<ans[i]<<" \n"[i==2];
    }
  }


}
