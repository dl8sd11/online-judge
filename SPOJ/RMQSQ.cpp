#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 3;
const int MAXLG = __lg(MAXN) + 2;

int n,q;
int st[MAXLG][MAXN];

void build(){
  for(int i=1;i<MAXLG;i++){
    for(int j=0;j<MAXN;j++){
      if(j+(1<<(i-1)) >= MAXN)continue;
      st[i][j] = min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
    }
  }
}

int query(int l,int r){ // [l,r]
  int E = __lg(r-l);
  return min(st[E][l],st[E][r-(1<<E)+1]);
}

int main(){
  cin>>n;
  for(int i=0;i<n;i++)cin>>st[0][i];
  cin>>q;
  build();
  int l,r;
  while(q--){
    cin>>l>>r;
    cout<<query(l,r)<<endl;
  }
}
