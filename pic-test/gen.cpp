#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

using ll = long long;
void rnd_circ (int n, int up) {
    ll r = 3e8;
    ll cen = 5e8;
    for (int i=0; i<n; i++) {
        
        ll dx = rand() % int(2e8);
        ll dy = sqrt(r*r - dx*dx);
        if (up == 1) {
            cout << cen + dx << " " << cen + dy << endl;
        } else {
            cout << cen -dx << " " << cen - dy << endl;
        }
    }

}

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    srand(time(0));
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    cout << n << " " << m << endl;

    rnd_circ(n, 0);
    rnd_circ(m, 1);
}

