#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

const int MAXN = 30003;
const int K = int(sqrt(MAXN));
int n,p,l,r,idx;
int a[MAXN];
struct QUERY{
  int l,r,id,Lid;
  QUERY(int li,int ri):l(li),r(ri),id(idx++){Lid = l/K;}
  bool operator < (const QUERY &h){
    if(Lid!=h.Lid)return Lid<h.Lid;
    else return r < h.r;
  }
};
vector<QUERY> Q;

int cnt[1000003],ans[200001],num;
void add(int x){
  //cout<<"ADD: "<<x<<endl;
  if(cnt[a[x]]==0)num++;
  cnt[a[x]]++;
}
void sub(int x){
  //cout<<"SUB: "<<x<<endl;
  cnt[a[x]]--;
  if(cnt[a[x]]==0)num--;
}
int main(){
  while(cin>>n){
    Q.clear();
    memset(cnt,0,sizeof cnt);
    num = 0;
    for(int i=0;i<n;i++)cin>>a[i];
    cin>>p;
    for(int i=0;i<p;i++){
      cin>>l>>r;
      l--,r--;
      Q.emplace_back(l,r);
    }

    sort(Q.begin(),Q.end());

    int L=0,R=-1;


    
    for(auto q:Q){
      //cout<<"DEE: "<<q.l<<" "<<q.r<<L<<" "<<R<<endl;
      while(L>q.l)add(--L);
      while(R<q.r)add(++R);
      while(L<q.l)sub(L++);
      while(R>q.r)sub(R--);
      ans[q.id] = num;
    }

    for(int i=0;i<p;i++){
      cout<<ans[i]<<" \n"[i==p-1];
    }
  }
}
