#include <bits/stdc++.h>
using namespace std;
int main (){
  double r,x,y,u,v;
  cin>>r>>x>>y>>u>>v;
  double dis = sqrt((x-u)*(x-u)+(y-v)*(y-v));
  cout<<fixed<<setprecision(10);
  cout<<dis<<endl;
  if (dis>=(r-1e-6)) cout<<x<<' '<<y<<' '<<r<<endl;
  else {
    if (u==x&&v==y) cout<<x+(r/2)<<' '<<y<<' '<<r/2<<endl;
    else  cout<<u-(u-x)*(dis+r)/2/dis<<' '<<v-(v-y)*(dis+r)/2/dis<<' '<<(dis+r)/2<<endl;
  }
}
