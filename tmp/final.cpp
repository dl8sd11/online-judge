#include <iostream>
using namespace std;

int main() {
  int l,r,ret=0;
  cin>>l>>r;

  for (int i=l;i<=r;i++) {
    int tmpi =i;
    while(tmpi) {
      if (tmpi%10==1)ret++;
      tmpi/=10;
    }
  }
  cout<<ret<<endl;
}
