#include <iostream>
using namespace std;

int a[9] = {4,7,2,9,9,0,4,4,3};
int q,x,y,z;
int main() {
  cin >> q;
  while (q--) {
    cin >> x >> y >> z;
    cout << (a[x-1] ^ a[y-1] ^ a[z-1]) << endl;
  }
}