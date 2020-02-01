#include <bits/stdc++.h>
using namespace std;
#define ALL(i) i.begin(),e.end()
#define pb push_back

const int MAXN = 100004;
int disj[MAXN],sz[MAXN];
void init(){
  for(int i=0;i<MAXN;i++){
    disj[i] = i;
    sz[i] = 0;
  }
}
int Find(int x){
  return (disj[x]==x?x:disj[x]=Find(disj[x]));
}
void Union(int x,int y){
  if(sz[x=Find(x)] > sz[y=Find(y)]) swap(x,y);
  disj[x] = y;
  sz[y] += sz[x];
}
int main(){
  int n,q,cmd,x,y;
  cin>>n>>q;
  init();
  while(q--){
    cin>>cmd>>x>>y;
    if(cmd==1){
      Union(x,y);
    } else {
      if(Find(x)==Find(y))cout<<"Yes"<<endl;
      else cout<<"No"<<endl;
    }
  }

}
