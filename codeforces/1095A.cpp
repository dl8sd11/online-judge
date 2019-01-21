#include <bits/stdc++.h>
using namespace std;

int main () {
    int n;
    string s;
    cin >> n >> s;
    int sum = 0;
    for (int i=1;sum+i<=n;i++) {
        sum += i;
        cout << s[sum-1];
    }

    cout << endl;
}