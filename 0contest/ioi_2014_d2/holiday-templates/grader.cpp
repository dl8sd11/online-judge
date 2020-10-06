#include<cstdio>
#include <bits/stdc++.h>
using namespace std;
#include"holiday.h"

int main() {
    int n, start, d;
    int attraction[100000];
    int i, n_s;
    //n_s = scanf("%d %d %d", &n, &start, &d);
    //for (i = 0 ; i < n; ++i) {
	//n_s = scanf("%d", &attraction[i]);
    //}
    //
    //

    while (true) {

        n = 10;
        start = 0;
        d = rand() % (n*2 + n/2);
        for (int i=0; i<n; i++) {
            attraction[i] = rand() % 30;
        }
        printf("%lld\n", findMaxAttraction(n, start, d,  attraction));
    }
    return 0;
}
