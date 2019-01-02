#include <bits/stdc++.h>
using namespace std;

struct Q{
  int cmd,u,v;
  Q(int cmdi,int ui,int vi):cmd(cmdi),u(ui),v(vi){}
};

const int MAXN = 100003;
vector<Q> qu;
vector<pair<int,int> > edge;
bool del[MAXN*3];
int n,m,q,x,y,cmd;
int sz[MAXN];
int disj[MAXN];
vector<bool> ans;


void init(){
  for(int i=0;i<MAXN;i++){
    disj[i] = i;
    sz[i] = 1;
  }
}

int Find(int xx){
  return xx==disj[xx]?xx:disj[xx]=Find(disj[xx]);
}

void Union(int xx,int yy){

  if(sz[xx=Find(xx)] > sz[yy=Find(yy)])swap(xx,yy);
  disj[xx] = yy;
  sz[yy] += sz[xx];
}
int main(){
  cin>>n>>m>>q;
  while(m--)cin>>x>>y,edge.emplace_back(x,y);
  while(q--){
    cin>>cmd;
    if(cmd==1){
      cin>>x;
      del[x-1] = 1;
      qu.emplace_back(1,edge[x-1].first,edge[x-1].second);
    } else {
      cin>>x>>y;
      qu.emplace_back(2,x,y);      
    }
  }

  init();
  for(int i=0;i<int(edge.size());i++){
    if(!del[i]){
      Union(edge[i].first,edge[i].second);
    }
  }


  for(auto it = qu.rbegin();it!=qu.rend();it++){
    if(it->cmd==1){
      Union(it->u,it->v);
    } else {
      ans.emplace_back(Find(it->u)==Find(it->v));
    }
  }

  for(auto it = ans.rbegin();it!=ans.rend();it++){
    if(*it)cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
  }
}
