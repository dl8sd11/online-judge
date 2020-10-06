#include <bits/stdc++.h>
using namespace std;

int main () {
    long long sum=0, bs = 1;

    int cnt = 0;
    for (bs=1; sum<200000; bs=bs*bs+1) {
        sum += bs;
        cout << bs << " ";
        cnt++;
    }

    cout << endl << cnt << endl;
}
