#include <iostream>
#include <string>
using namespace std;

int main () {
    string a, b;
    cin >> a;
    cin >> b;
    bool ev = true;
    int ans = 0, bk = 0;
    for (int i=0;i<int(b.size());i++) {
        if (b[i] != a[i]) {
            ev = !ev;
        }
        if (i && a[i] != a[i-1]) {
            bk++;
        } 
    }
    ans += ev;
    for (int i=1;i<=int(a.size()-b.size());i++) {
        bk += a[i+b.size()-2] != a[i+b.size()-1];
        ev ^= (bk & 1);
        ans += ev;
        bk -= a[i] != a[i-1];
    }

    cout << ans << endl;
}

