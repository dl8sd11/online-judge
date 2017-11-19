#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;
#define REP(i,n) for(ll i=0;i<n;i++)

typedef long long ll;

ll money(string a){
  ll ret = 0;
  ll pt = ll(a.size()-1);
  ll times = 1;
  while(a[pt]<='9'&&a[pt]>='0'){
    ret += times * (a[pt]-'0');
    pt--;
    times*=10;
  }
  return ret;
}
string test1;
int main(){
  ll t;
  cin>>t;
  getline(cin,test1);
  for(ll i=0;i<t;i++){
    ll s,n;
    cin>>s>>n;
    getline(cin,test1);
    std::map<string, ll> cost;
    REP(j,s){
      string itemName;
      string price;
      cin>>itemName>>price;
      getline(cin,test1);
      cost[itemName] = money(price);
      //cout<<"add map: "<<itemName<<"->"<<money(price)<<endl;
    }
    std::vector<pair<int,string> > v;
    for(ll j=0;j<n;j++){
      //cout<<"DED "<<j<<endl;
      string foodLine;

      getline(cin,foodLine);
      //cout<<"Got Line: "<<foodLine<<endl;
      stringstream ss;
      ss<<foodLine;
      string foodID,tmp;
      ll value;
      ll costSum = 0;
      ss>>foodID;
      ss>>tmp;
      value = money(tmp);
      ss>>tmp;
      int times;
      while(ss>>times){
        string itemName;
        ss>>itemName;
        costSum += times * cost[itemName];
        if(cost[itemName]==0)costSum+=ll(1e10);
      }


      if(costSum<value){
        v.push_back(make_pair(money(foodID),foodID));
      }
    }
    sort(v.begin(),v.end());
    ll vs = int(v.size());
    if(vs==0)
      cout<<"no such recipe."<<endl;
    REP(k,vs){
      if(k!=vs-1)cout<<v[k].second<<'/';
      else cout<<v[k].second<<endl;
    }
  }
}
