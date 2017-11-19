#include <bits/stdc++.h>
using namespace std;
#define FOR(a,b,c,d) for(int a=b;a<c;a++)
#define REP(i,n) for(int i=0;i<n;i++)
#define PB push_back
typedef long long ll;
typedef vector<int> vi;

ll ct[2];
vi e[100007];

void dfs(int node,int pnode,bool st)
{
  ct[st]++;
  int len = int(e[node].size());
  for(int i=0;i<len;i++){
    if(e[node].at(i)!=pnode)
      dfs(e[node].at(i),node,!st);
  }
  return;
}

int main()
{
  int n;
  cin>>n;
  REP(i,n-1){
    int u,v;
    cin>>u>>v;
    e[u].PB(v);
    e[v].PB(u);
  }
  ct[0]=0;
  ct[1]=0;
  dfs(1,0,0);

  cout<<ct[0]*ct[1]-n+1<<endl;
}
