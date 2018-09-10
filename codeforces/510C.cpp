#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<n;i++)
int n;
vector<char> answer;
bool used[27];
string s[103];
bool edge[27][27];
int degree[27];
void makeGraph(string &a,string &b) {
  int lena = int(a.size());
  int lenb = int(b.size());
  int i=-1,j=-1;
  while(++i<lena&&++j<lenb) {
    if (a[i]!=b[j]) {
      if (!edge[b[j]-'a'][a[i]-'a']) {
	edge[b[j]-'a'][a[i]-'a'] = 1;
	degree[a[i]-'a']++;
	used[a[i]-'a']=1;
	used[b[j]-'a']=1;
	break;
      }
    }
  }
}
bool makeDic() {
  queue<int> BFS;
  REP(i,26) if (!used[i]) answer.push_back(i+'a');
  REP (i,26) if (degree[i]==0&&used[i]) BFS.push(i);
  while(BFS.size()) {
    REP(i,26) {
      if (edge[BFS.front()][i]) {
	degree[i]--;
	if (degree[i]==0) BFS.push(i);
      }
    }
    used[BFS.front()]=0;
    answer.push_back(BFS.front()+'a');
    BFS.pop();
  }
  REP (i,26) if(used[i]) return false;
  return true;		   
}
int main() {
  cin>>n;
  REP(i,n) cin>>s[i];
  for (int i=1;i<n;i++) {
    makeGraph(s[i-1],s[i]);
  }
  if (makeDic()) for(int i=int(answer.size()-1);i>=0;i--) cout<<answer[i];
  else cout<<"Impossible"<<endl;
}
