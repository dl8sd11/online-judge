#include <bits/stdc++.h>
using namespace std;

int main () {
    int a[100], n, sum = 0;

    cin >> n;

    for (int i=0; i<n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    sort(a, a+n);
    reverse(a, a+n);

    int tmp = 0;
    for (int i=0; i<n; i++) {
        tmp += a[i];

        if (tmp > sum-tmp) {
            cout << i+1 << endl;
            return 0;
        }
    }
}
