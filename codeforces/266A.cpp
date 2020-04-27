#include <bits/stdc++.h>
using namespace std;

int main () {
    int n;
    
    cin >> n;

    int ans = 0;
    char lst = '@';
    for (int i=0; i<n; i++) {
        char c;
        cin >> c;

        if (lst == c) {
            ans++;
        }
        lst = c;
    }

    cout << ans << endl;
}
