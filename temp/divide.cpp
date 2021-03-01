#include <bits/stdc++.h>
using namespace std;

int mpow (int base, int ep) {
    return ep == 0 ? 1 : base * mpow(base, ep-1);
}

int main () {
    int n;
    cin >> n; // number of treasures

    int value[10] = {};
    for (int i=0; i<n; i++) {
        cin >> value[i];
    }

    int size;
    cin >> size;

    bool has_ans = false;
    for (int mask=0; mask<mpow(3, n); mask++) {
        int cur = mask;
        int total[3] = {};
        int cap[3] = {};
        for (int j=0; j<n; j++) {
            total[cur%3] += value[j];
            cap[cur%3]++;
            cur /= 3;
        }

        bool is_ans = true;
        for (int j=0; j<3; j++) {
            is_ans &= total[j] == total[0];
            is_ans &= cap[j] <= size;
        }


        has_ans |= is_ans;
    }

    cout << (has_ans ? "YES" : "NO") << endl;

}

