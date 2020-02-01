#include <bits/stdc++.h>
using namespace std;

int t,n,a[52],ans;
int djs[52],sz[52];
void init(){
  for(int i=0;i<n;i++){
    djs[i] = i;
    sz[i] = 1;
  }
}

int fnd(int x){
  return (djs[x]==x?x:djs[x]=fnd(djs[x]));
}

void uni(int x,int y){
  if(sz[x=fnd(x)] > sz[y=fnd(y)])swap(x,y);
  djs[x] = y;
  sz[y] += sz[x];
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin>>t;


  while(t--){
    cin>>n;
    for (int i=0;i<n;i++) {
      cin>>a[i];
    }

    init();
    for(int i=0;i<n;i++){
      for(int j=i+1;j<n;j++){
        if(__gcd(a[i],a[j])==1&&fnd(i)!=fnd(j))uni(i,j);
      }
    }
    ans = 0;
    int root = 0;
    for(int i=1;i<n;i++){
      if(fnd(i)!=fnd(root)){
        if(a[i] < a[root])swap(i,root);
        int gcd = __gcd(a[i],a[root]);
        if(__gcd(a[i]/gcd,a[root])!=1)a[i]=a[root]+1;
        else a[i] /= gcd;
        ans++;
        for(int j=0;j<n;j++){
          if(j==i)continue;
          if(__gcd(a[i],a[j])==1&&fnd(i)!=fnd(j))uni(i,j);
        }
      }
    }
#ifdef tmd
cout<<endl<<endl;
#endif
    cout<<ans<<endl;
    for(int i=0;i<n;i++)cout<<a[i]<<" \n"[i==n-1];
  }
}
