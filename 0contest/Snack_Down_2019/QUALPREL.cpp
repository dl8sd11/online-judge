#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 100003;
ll t,n,k,a[MAXN];
bool cmp (const int &c,const int &b){
  return c > b;
}
int main(){
  ios_base::sync_with_stdio(0);cin.tie(0);

  cin>>t;
  while(t--){
    cin>>n>>k;
    for(ll i=0;i<n;i++)cin>>a[i];
    sort(a,a+n,cmp);
    cout<<upper_bound(a,a+n,a[k-1],cmp)-a<<" \n";
  }
}
