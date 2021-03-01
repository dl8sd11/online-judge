#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<n;i++)
int m,r,b,tmp;
int cntr[503],cntb[503];
int main () {
  ios::sync_with_stdio(0);
  cin.tie(0);
  while (cin>>m) {
    r=0;b=0;
    REP(i,m) {
      cin>>tmp;
      cntr[tmp]++;
    }
    REP(i,m) {
      cin>>tmp;
      cntb[tmp]++;
    }
    
    long long ret = 0;
    REP(i,m) {
      while(!cntr[r]) r++;
      while(!cntb[b]) b++;
      ret+=r*b;
      cntr[r]--;cntb[b]--;
    }
    cout<<ret<<endl;
  }
}
