#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll t,n,h,w,tmp;
__int128 sum;
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);
  cin>>t;
  while(t--){
    cin>>n>>h>>w;
    sum = 0;
    for(ll i=0;i<n;i++)cin>>tmp,sum += tmp;

    if(sum == w*h) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
  }
}
