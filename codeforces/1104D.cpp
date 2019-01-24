#include <bits/stdc++.h>
using namespace std;

string str;
int bit;

char query(int x,int y) {
    char ret;
    cout << "? " << x << " " << y << endl;
    cin >> ret;
    return ret;
}
int main () {
    while (cin>>str && str == "start") {
        if (query(0,1) == 'x') {
            cout << "! 1" << endl;
            continue;
        }
        for (bit=0;;bit++) {
            if (query(1<<bit,1<<bit+1) == 'x') {
                break;
            }
        }
        int L = 1 << bit,R = 1 << bit + 1;
        while (L < R - 1) {
            int mid = L + R >> 1;
            if (query(mid,L) == 'y') {
                R = mid;
            } else {
                L = mid;
            }
        }

        cout << "! " << L+1 << endl;
    }
}