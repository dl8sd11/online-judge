#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300000;
const int k = int(sqrt(MAXN));

int n,m,l,r,a[MAXN];
set<int> rcnt[MAXN];
int cnt[66000];
int mx;
struct QUERY{
  int l,r,id,Lid;
  QUERY(int li,int ri,int idi):l(li),r(ri),id(idi){
    Lid = id / k;
  }

  bool operator < (const QUERY &b){
    if(b.Lid!=Lid)return Lid<b.Lid;
    else if(b.Lid&1)return r>b.r;
    else return r<b.r;
  }
};

void sub(int x){
  if(rcnt[cnt[x]].size())rcnt[cnt[x]].erase(x);
  if(rcnt[cnt[x]].empty() && mx == cnt[x])mx--;
  cnt[x]--;
  rcnt[cnt[x]].insert(x);
}

void add(int x){
  if(rcnt[cnt[x]].size())rcnt[cnt[x]].erase(x);
  cnt[x]++;
  rcnt[cnt[x]].insert(x);
  if(cnt[x]>mx)mx = cnt[x];

}
vector<QUERY> q;
int ans[MAXN];
int main(){
  cin>>n>>m;
  for(int i=0;i<n;i++)cin>>a[i];
  int li,ri;
  for(int i=0;i<m;i++)cin>>li>>ri,q.emplace_back(li-1,ri-1,i);
  sort(q.begin(),q.end());
  int L = 0,R = -1;
  for(auto Q:q){
    while(L>Q.l)L--,add(a[L]);
    while(R<Q.r)R++,add(a[R]);
    while(L<Q.l)sub(a[L]),L++;
    while(R>Q.r)sub(a[R]),R--;

    if(mx>(R-L+1)/2)ans[Q.id] = *rcnt[mx].begin();
    else ans[Q.id] = -1;
  }
  for(int i=0;i<m;i++){
    cout<<ans[i]<<endl;
  }
}
