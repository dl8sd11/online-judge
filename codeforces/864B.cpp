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

  char s[n];
  cin>>s;

  int ans =0;
  bool alpha[26];
  memset(alpha,0,sizeof(alpha));

  REP(i,n){

    if(s[i]>='a')
      alpha[s[i]-'a']=1;
    else{
      int sum =0;
      for(int j=0;j<26;j++){
        sum += alpha[j];
      }
      memset(alpha,0,sizeof(alpha));
      ans = max(ans,sum);
    }

  }
  int sum =0;
  for(int j=0;j<26;j++){
    sum += alpha[j];
  }

  ans = max(ans,sum);

  cout<<ans<<endl;
}
