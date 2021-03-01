#include <bits/stdc++.h>
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

  int ck[2];
  ck[0]=0;
  ck[1]=0;
  int ct[2];
  ct[0]=0;
  ct[1]=0;
  REP(i,n){
    int tmp;
    cin>>tmp;

    if(tmp==ck[0]){
      ct[0]+=1;
    }
    else if(tmp==ck[1]){
      ct[1]+=1;
    }
    else if(ck[0]==0){
      ck[0]=tmp;
    }
    else if(ck[1]==0){
      ck[1]=tmp;
    }
    else{
      cout<<"NO"<<endl;
      return 0;
    }
  }
  if(ct[0]==ct[1]){
    cout<<"YES"<<endl;
    cout<<ck[0]<<' '<<ck[1]<<endl;
  }
  else{
    cout<<"NO"<<endl;
  }


}
