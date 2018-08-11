#include <bits/stdc++.h>
using namespace std;
bool cmp(char &a,char &b){
  cout<<"? "<<a<<" "<<b<<endl<<flush;
  char ans;
  cin>>ans;
  return ans=='<';
}
int main(){
  int n,q;
  cin>>n>>q;
  vector<char> a;
  for(int i=0;i<n;i++)a.push_back('A'+i);
  sort(a.begin(),a.end(),cmp);
  cout<<"! ";
  for(char &c:a)cout<<c;
  cout<<endl<<flush;

  return 0;
}
