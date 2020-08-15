#include <bits/stdc++.h>
using namespace std;


int main () {
    int x, sum = 0, y = 0;
    while (cin >> x) {
        assert(x == 0 || x == 1);
        sum += x;
        system("clear");
        y++;
    }

    cout << sum << "/" << y << endl;

}
