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
  int a,b,f,k;
  cin>>a>>b>>f>>k;

  int aDis = f;
  int bDis = a-f;
  int a2Dis = aDis * 2;
  int b2Dis = bDis * 2;
  int tank = b-aDis;

  //check -1
  if(b<aDis||b<bDis){
    cout<<-1<<endl;
    return 0;
  }
  if(k>2){
    if(b<aDis*2||b<bDis*2){
      cout<<-1<<endl;
      return 0;
    }
  }
  if(k==2){
      if(b<bDis*2){
        cout<<-1<<endl;
        return 0;


      }
  }

  int ans = 0;
  bool dir = 1;
  while(k>1){
    if(dir){
      if(b2Dis>tank){
        tank = b;
        ans++;
      }
      k--;
      tank-=b2Dis;
    }
    else{
      if(a2Dis>tank){
        tank = b;
        ans++;
      }
      k--;
      tank -=a2Dis;
    }
    dir = !dir;
  }
  if(dir){
    if(bDis>tank){
      ans++;
    }
  }
  else{
    if(aDis>tank){
      ans++;
    }
  }
  cout<<ans<<endl;
}
