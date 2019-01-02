#include <bits/stdc++.h>
using namespace std;

int t,n,sz[52],djs[52],dp[52][52];
string name[52];

int LCS(string s1,string s2){
  memset(dp,0,sizeof dp);
  for(int i=1;i<=int(s1.size());i++) {
    for(int j=1;j<=int(s2.size());j++) {
      if(s1[i-1] == s2[j-1]) {
        dp[i][j] = dp[i-1][j-1] + 1;
      } else {
        dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
      }
    }
  }
  return dp[s1.size()][s2.size()];
}
void init(){
  for(int i=0;i<52;i++){
    sz[i] = 1;
    djs[i] = i;
  }
}

int fnd(int tg) {
  return tg == djs[tg] ? tg : djs[tg] = fnd(djs[tg]);
}

void uni(int e1,int e2){
  if(sz[e1=fnd(e1)] < sz[e2=fnd(e2)])swap(e1,e2);
  djs[e2] = e1;
  sz[e1] += sz[e2];
}
int main() {
  cin>>t;
  while(t--){
    cin>>n;
    for(int i=0;i<n;i++)cin>>name[i];
    init();
    for(int i=0;i<n;i++){
      for(int j=i+1;j<n;j++){
        if(LCS(name[i],name[j]) >= min(name[i].size(),name[j].size())/2.0) {
          // cout<<"HEY"<<endl;
          if(fnd(i) != fnd(j)) uni(i,j);
        }
      }
    }

    int bst = -1;
    for(int i=0;i<n;i++){
      bst = max(sz[fnd(i)],bst);
    }
    cout<<bst<<endl;
  }
}
