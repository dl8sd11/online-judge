#include <bits/stdc++.h>
#include <queue>
using namespace std;
#define FOR(a,b,c,d) for(int a=b;a<c;a++)
#define REP(i,n) for(int i=0;i<n;i++)
#define PB push_back
#define MP make_pair
#define endl '\n'
typedef long long ll;
typedef vector<int> vi;

int main()
{
  int n;
  cin>>n;
  queue<int> rep[n+3];
  bool used[n+3];
  int status[n+3];
  int ans[n+3];
  memset(used,0,sizeof(used));
  memset(status,0,sizeof(status));
  REP(i,n){
    int tmp;
    cin>>tmp;
    rep[tmp].push(i+1);
    ans[i+1] = tmp;
    if(used[tmp]){
      status[i+1] = 1;
      status[rep[tmp].front()]=1;
    }
    else{
      used[tmp]=1;
    }
  }

  queue<int> unu;
  REP(i,n){
    if(!used[i+1])
      unu.push(i+1);
  }

  int man = 0;
  FOR(i,1,n+1,1){
    if(!unu.size()){
      break;
    }
    if(status[i]==1){
      if(unu.front()<ans[i]){
        int repsize = int(rep[ans[i]].size());
        if(repsize>1){
          man++;
          rep[ans[i]].pop();
          ans[i] = unu.front();
          unu.pop();
        }
      }
      else{
        int repsize = int(rep[ans[i]].size());
        for(int j=0;j<repsize;j++){
          int x = rep[ans[i]].front();
          status[x]=2;
          rep[ans[i]].pop();
        }

      }
    }
    else if(status[i]==2){
      ans[i] = unu.front();
      unu.pop();
      man++;
    }
  }

  cout<<man<<endl;
  REP(i,n){
    cout<<ans[i+1]<<' ';
  }
  // cout<<endl;
  //
  // cout<<"Status: ";
  // REP(i,n){
  //   cout<<status[i+1]<<' ';
  // }
  // cout<<endl;
  //
  // cout<<"Used: ";
  // REP(i,n){
  //   cout<<used[i+1]<<' ';
  // }
  // cout<<endl;
}
