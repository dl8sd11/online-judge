#include <bits/stdc++.h>
using namespace std;
typedef pair<double,double> pdd;

pdd operator-(pdd &a,pdd &b){return make_pair(a.X-b.X,a.Y-b.Y);}
pdd operator*(pdd &a,pdd &b){return make_pair(a.X*b.Y-a.Y*b.X);}
int n,x,y;
vector<pdd> p;
int main(){
  cin>>n;
  for(int i=0;i<n;i++)cin>>x>>y,p.push_back({x,y});
  sort(p.begin(),p.end());
  
}
