#include <bits/stdc++.h>
using namespace std;

int n,used[1007];
vector<int> input;
vector<int> output;
int main(){
  cin>>n;
  int tmp;
  while(n--){
    cin>>tmp;
    input.push_back(tmp);
  }
  reverse(input.begin(),input.end());
  for(auto it:input){
    if(!used[it])output.push_back(it);
    used[it] = true;
  }
  cout<<output.size()<<endl;
  for(auto it=output.rbegin();it!=output.rend();it++){
    cout<<*it<<' ';
  }
  cout<<endl;
}
