#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;


int sec(string x){
  stringstream ss;
  int tmp,rtn=0;
  ss<<x.substr(0,2);
  ss>>tmp;
  rtn+=tmp*3600;
  ss.clear();
  ss.str("");
  ss<<x.substr(3,2);
  ss>>tmp;
  rtn+=tmp*60;
  ss.clear();
  ss.str("");
  ss<<x.substr(6,2);
  ss>>tmp;
  rtn+=tmp;
  return rtn;
}
int main(){
  string a,b;
  cin>>a>>b;
  int gap = sec(b)-sec(a);
  if(gap <0)gap+= 24*3600;
  cout<<setw(2)<<setfill('0');
  cout<<gap/3600<<":";cout<<setw(2);
  cout<<(gap%3600)/60<<":";cout<<setw(2);
  cout<<(gap%60);
}
