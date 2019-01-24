#include <bits/stdc++.h>
using namespace std;
string s;
int cnt1,cnt2;
int main () {
    cin >> s;
    for (auto c : s) {
        if (c == '0') {
            cout << 1 << " " << (cnt1++) % 4 + 1 << endl;
        } else {
            cout << 4 << " " << (cnt2++) % 2 * 2 + 1 << endl;
        }
    }
}