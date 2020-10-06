#include <bits/stdc++.h>
#include "jngen.h"
using namespace std;

int main (int argc, char *argv[]) {
    parseArgs(argc, argv);

    int n = 10000, q = 10000;
    jngen::getPositional(n, q);
    auto t = Tree::random(n).shuffled();
    t.setEdgeWeights(Array::random(n-1, 1, 1000000000));

    cout << n << " " << q << endl;
    cout << t.add1() << endl;

    vector<int> on(n, 0);
    int cnt = 0;
    for (int i=0; i<q; i++) {
        if (cnt == 0 || rand() % 2 == 0) {
            int idx = rnd.next(0, n-1);
            on[idx] ^= 1;
            if (on[idx]) {
                cnt ++;
                cout << 1 << " " << idx + 1 << endl;
            } else {
                cnt --;
                cout << 2 << " " << idx + 1 << endl;
            }
        } else {
            cout << 3 << " " << rnd.next(1,n) << " " << rnd.next(1, cnt) << endl;
        }

    }
}
