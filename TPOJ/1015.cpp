#include <bits/stdc++.h>
using namespace std;



const int MAXN = 2005;
int BIT[MAXN][MAXN];
int n,q;
int cmd,tx1,tx2,ty1,ty2,tz;

void add(int x,int y,int val){
  for(;x<=n;x+=-x&x){
    for(int i=y;i<=n;i+=-i&i){
      BIT[x][i] += val;
    }
  }
}

int query(int x,int y){
  if(!x||!y) return 0;
  int ret = 0;
  for(;x>=1;x-=-x&x){
    for(int i=y;i>=1;i-=-i&i){
      ret += BIT[x][i];
    }
  }
  return ret;
}


int main(){
  cin>>n>>q;
  for(int i=0;i<q;i++){
    cin>>cmd;
    if(cmd==1){
      cin>>tx1>>ty1>>tz;
      tx1++,ty1++;
      add(tx1,ty1,tz);
    }else{
      cin>>tx1>>ty1>>tx2>>ty2;
      tx1++,tx2++,ty1++,ty2++;

      cout<<query(tx2,ty2) - query(tx1-1,ty2-1) -query(tx2-1,ty1-1) + query(tx1-1,ty1-1)<<endl;
    }
  }
}
