#include <bits/stdc++.h>
using namespace std;

int main(){
  map<string,vector<int>> m;
  int t;
  cin>>t;
  while(t--){
    int n;
    string s;
    cin>>s;
    cin>>n;
    vector<int> v;
    while(n--){
      int tmp;
      cin>>tmp;
      v.push_back(tmp);
    }
    m[s] = v;
    cout<<"INPUTED"<<endl;
  }
  string key;
  while(cin>>key){
    for(auto a:m[key]){
      cout<<a<<' ';
    }
    cout<<endl;
  }
}
