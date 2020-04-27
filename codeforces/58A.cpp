#include <bits/stdc++.h>
using namespace std;

string s;

string t = "hello@";
int main () {
    cin >> s;

    int id = 0;
    for (auto c : s) {
        if (c == t[id]) {
            id++;
        }
    }

    if (id == 5) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}
