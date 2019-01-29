#include <bits/stdc++.h>
using namespace std;

int main () {
    int n  = 3635;
    cout << n << endl;
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            cout << 100 << " \n"[j==n-1];
        }
    }
}