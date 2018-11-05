#include <bits/stdc++.h>
using namespace std;


int n;
int a[30][30];
int sum(int sx,int sy,int ex,int ey){
  int ret = 0;
  for(int i=sx;i<=ex;i++){
    for(int j=sy;j<=ey;j++){
      ret += a[i][j];
    }
  }
  return ret;
}
int main() {
  cin>>n;
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      cin>>a[i][j];
    }
  }

  int mx = 0;
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      for(int k=i;k<n;k++){
        for(int l=j;l<n;l++){
          mx = max(mx,sum(i,j,k,l));
        }
      }
    }
  }

  cout<<mx<<endl;
}
