#include <bits/stdc++.h>
using namespace std;

int main () {
    int d,sum = 1;
    while (cin >> d) {
        for (int i=2;i*i<=d;i++) {
            if (d % i == 0) {
                cout << -1 << endl;
                return 0;
            }
        }
        sum *= d;
    }
    cout << sum << endl;
}