#include <bits/stdc++.h>
using namespace std;

#define mmax(a,b) ((a)>(b)?(a):(b))

int n,mx,sm,tp;
long long lsm;
/********** Main()  function **********/
int main()
{
  ios_base::sync_with_stdio(0);cin.tie(0);
  while(cin>>n&&n!=0){
    if(n<46400){
      mx = -1,sm = 1;
      for(int i=0;i<n;i++){
        cin>>tp;
        sm += tp;
        mx = mmax(mx,tp);
      }
      sm += mx;
      cout<<sm<<'\n';
    } else {
      mx = -1,lsm = 1;
      for(int i=0;i<n;i++){
        cin>>tp;
        lsm += tp;
        mx = mmax(mx,tp);
      }
      lsm += mx;
      cout<<lsm<<'\n';
    }


  }
	return 0;
}
