#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100004;
int p[MAXN], q[MAXN];
int main () {
    int n = 1000, k = 0;
    cout << n << " " << k << endl;
    for (int i=0; i<n; i++) {
        p[i] = q[i] = n-i;
    }

    // int lst = -1;
    // for (int i=0; i<n; i++) {
    //     if (rand() % 10 == 0)  {
    //         random_shuffle(q+lst+1, q+i+1);
    //         lst =i;
    //     }
    // }

    vector<pair<int,int> > vp;
    for (int i=0; i<n; i++) {
        vp.emplace_back(p[i], q[i]);
    }
    // random_shuffle(vp.begin(), vp.end());

    for (int i=0; i<n; i++) {
        cout << vp[i].first << " \n"[i==n-1];
    }
    for (int i=0; i<n; i++) {
        cout << vp[i].second << " \n"[i==n-1];
    }
}