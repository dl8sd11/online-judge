#include <iostream>

using namespace std;


int n;
int pos, neg;
int main() {

    cin >> n;

    long long ans = 0;
    for (int i=0;i<n;i++) {
      int a;
      cin >> a;
      if (a == 0) {
        pos = neg = 0;
      } else if (a > 0) {
        pos++;
      } else {
        pos++;
        swap(pos,neg);
      }
      ans += pos;
    }

    cout << ans << endl;
    return 0;
}
