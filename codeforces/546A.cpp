#include <bits/stdc++.h>
using namespace std;

int main () {
    int k, n, w;

    cin >> k >> n >> w;

    int cost = w*(w+1)*k/2;

    cout << max(0, cost - n) << endl;
}
