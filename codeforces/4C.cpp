#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = ll(1e9)+103;
ll n;
string tmp;
map<ll,ll> db;
ll hashf(string s) {
  ll times = 1;
  ll ret=0;
  for(auto c:s) {
    ret+=c*times;
    ret%=MOD;
    times = (times*880301)%MOD;
  }
  return ret;
}
int main(){
  cin>>n;
  for(ll i=0;i<n;i++ ) {
    cin>>tmp;
    ll data = hashf(tmp);
    ll searchd=db[data];
    if(searchd)cout<<tmp<<(db[data]++)<<endl;
    else cout<<"OK"<<endl,db[data]=1;
  }
}
