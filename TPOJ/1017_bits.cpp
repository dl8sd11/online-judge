#include <bits/stdc++.h>
using namespace std;

#define ALL(i) i.begin(),i.end()
const int MAXN = 300003;
const int MAXLG = 17; 
int n,q,tmp,l,r;
int bits[MAXLG][MAXN];
vector<int> num[MAXN];
int main(){
  cin>>n>>q;
  for(int i=1;i<=n;i++){
    cin>>tmp;
    num[tmp].push_back(i);
    for(int j=0;j<MAXLG;j++){
      if(tmp&1)bits[j][i]++;
      tmp >>= 1;
      bits[j][i] += bits[j][i-1];
    }
  }

  while(q--){
    cin>>l>>r;
    int ret = 0;
    for(int i=0;i<MAXLG;i++){
      if(bits[i][r] - bits[i][l-1] > (r-l+1)/2)ret|=1<<i;
    }
    if(upper_bound(ALL(num[ret]),r) - lower_bound(ALL(num[ret]),l) > (r-l+1)/2) cout<<ret<<endl;
    else cout<<-1<<endl;
  }
}
