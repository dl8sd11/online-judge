#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;


int main(int argc, char* argv[]) {
    assert(argc > 5);
    registerGen(argc, argv, 1);
    int N = atoi(argv[1]);
    int K = atoi(argv[2]);
    int Q = atoi(argv[3]);
    int C = atoi(argv[4]);
    printf("%d %d\n", N, K);

    vector<int> arr(N);
	for (int i=0; i<N; i++) {
        arr[i] = rnd.next(1, C);
    }
    for (int i = 0; i < N; ++i)
        printf("%d%c", arr[i], " \n"[i == N-1]);

    printf("%d\n", Q);

    for (int i=0; i<Q; i++) {
        int L = rnd.next(1, N);
        int R = rnd.next(1, N);
        if (L > R) {
            swap(L, R);
        }
        printf("%d %d\n", L, R);
    }
}
