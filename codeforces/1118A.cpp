#include <bits/stdc++.h>
using namespace std;

int main () {
    int q;
    cin >> q;
    while (q--) {
        long long n;
        int a,b;
        cin >> n >> a >> b;
        if (2*a <= b) {
            cout << n * a << endl;
        } else {
            cout << (n>>1)*b + (n&1)*a << endl;
        }
    }
}