#include <bits/stdc++.h>
using namespace std;

int cnt1[100008];
int balance[100008];
int minIdx[200008];

int main(){
    int n;
    cin>>n;

    int lastCnt = 0;
    for(int i=0;i<200008;i++)
      minIdx[i] = 10000007;
    minIdx[0] = -1;
    for(int i=0;i<n;i++){

      char tmp;
      cin>>tmp;

      if(tmp=='1')
        lastCnt += 1;

      cnt1[i] = lastCnt;
      balance[i] = cnt1[i]*2 - i-1;
      int idx = balance[i];
      if(balance[i]<0)idx = abs(idx)+100000;
      minIdx[idx] = min(i,minIdx[idx]);

    }

    int ans =0;
    for(int i=0;i<n;i++){
      int idx = balance[i];
      if(balance[i]<0)idx = abs(idx)+100000;
      //cout<<i<<' '<<minIdx[idx]<<' '<<balance[i]<<' '<<idx<<endl;
      ans = max(ans,i-minIdx[idx]);
    }
    cout<<ans<<endl;
}
