#include <bits/stdc++.h>
using namespace std;
#define FOR(a,b,c,d) for(int a=b;a<c;a++)
#define REP(i,n) for(int i=0;i<n;i++)
#define PB push_back
typedef long long ll;
typedef vector<int> vi;


int main()
{
  int n,x;
  cin>>n>>x;
  vi s;
  REP(i,n){
    int tmp;
    cin>>tmp;
    s.PB(tmp);
  }

  sort(s.begin(),s.end());

  vi::iterator up;
  up = upper_bound(s.begin(),s.end(),x);
  long idx = up-s.begin();

  if(idx==0)
    cout<<x<<endl;
  else if(s.at(idx-1)==x)
    cout<<x-idx+2<<endl;
  else
    cout<<x-idx<<endl;


}
