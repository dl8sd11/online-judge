#include <bits/stdc++.h>
using namespace std;
#define SZ(i) int(i.size())
typedef long long ll;
typedef pair<ll,ll> pii;
#define X first
#define Y second
pii operator -(const pii &a,const pii &b){
  return make_pair(a.X-b.X,a.Y-b.Y);
}

ll operator *(const pii &a,const pii &b){
  return a.X*b.Y - a.Y*b.X;
}

vector<pii> p;
ll n,x,y;
vector<pii> cv;
void convex_hull(){
  cv.clear();

  for(int i=0;i<SZ(p);i++){
    while(SZ(cv) >= 2 && (p[i]-cv[SZ(cv)-1])*(cv[SZ(cv)-1]-cv[SZ(cv)-2])<0)cv.pop_back();
    cv.push_back(p[i]);
  }
  int m;
  m = SZ(cv);
  for(int i=SZ(p)-1;i>=0;i--){
    while(SZ(cv)-m >= 2 && (p[i]-cv[SZ(cv)-1])*(cv[SZ(cv)-1]-cv[SZ(cv)-2])<0)cv.pop_back();
    cv.push_back(p[i]);
  }

}
int main(){
  cin>>n;
  for(int i=0;i<n;i++)cin>>x>>y,p.push_back({x,y});
  sort(p.begin(),p.end());
  p.resize(unique(p.begin(),p.end())-p.begin());

  convex_hull();
  //  cout<<SZ(cv)<<endl
  sort(cv.begin(),cv.end());
  cv.resize(unique(cv.begin(),cv.end())-cv.begin());
  for(auto ans:cv){
    cout<<ans.first<<" "<<ans.second<<endl;;
  }

}
