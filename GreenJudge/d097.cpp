#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;
string tmp;
int n;
double num[30];
char ope[30];
double solve() {
  double ans = 0;
  double cur = num[0];
  bool na = 0;
  for (int i=0;i<n-1;i++) {
    if (ope[i] == '+' || ope[i] == '-') {
      ans += cur * (na?-1:1);
      na = ope[i] == '-';
      cur = num[i+1];
    } else if (ope[i] == '*') {
      cur *= num[i+1];
    } else {
      if(num[i+1] == 0)return -1e18;
      cur /= num[i+1];
    }
  }

  ans += cur*(na?-1:1);

  return ans;
}
int main() {
  getline(cin,tmp);
  stringstream ss;
  ss<<tmp;
  vector<double> vt;
  double xd;
  while(ss>>xd)vt.push_back(xd);
  n = vt.size();
  for (int i=0;i<n;i++) {
    num[i] = vt[i];
  }
  for (int i=0;i<n-1;i++) {
    cin>>ope[i];
  }
  sort(ope,ope+n-1);

  double bst = -1e10;
  do {
    double tmp = solve();
    bst = max(tmp,bst);
  } while(next_permutation(ope,ope+n-1));

  cout<<fixed<<setprecision(2)<<bst<<endl;
}