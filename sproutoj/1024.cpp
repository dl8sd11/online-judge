#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

ld pi (int k) {
    ld res = 2;
    for (int i=1; i<=k; i++) {
        res *= (4.0*i*i) / (2*i-1) / (2*i+1);
    }
    return res;
}

ld pi2 () {
    int t = 10000000;
    int c = 0;

    for (int i=0; i<t; i++) {
        ld x = rand()*1.0 / RAND_MAX;
        ld y = rand()*1.0 / RAND_MAX;

        if (x*x + y*y <= 1.0) {
            c++;
        }
    }

    return 4.0 * c / t;
}
int main () {
    int k;
    cin >> k;

    ld p13 = pi(k);
    cout << abs(p13 - pi2()) << endl;
}
