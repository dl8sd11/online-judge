#include "stdio.h"

int rec (int R, int a, int b, int c, int A, int B, int C, int lev) {
    if (lev == 3) {
        return R == 0;
    } else {
        int res = 0;
        if (lev == 0) {
            for (long long i=0; i<=a && i*A<=R; i++) {
                res |= rec(R - i*A, a, b, c, A, B, C, lev+1);
                if (res) return 1;
            }
        }
        if (lev == 1) {
            for (long long i=0; i<=b && i*B<=R; i++) {
                res |= rec(R - i*B, a, b, c, A, B, C, lev+1);
                if (res) return 1;
            }
        }
        if (lev == 2) {
            for (long long i=0; i<=c && i*C<=R; i++) {
                res |= rec(R - i*C, a, b, c, A, B, C, lev+1);
                if (res) return 1;
            }
        }
        return res;
    }
}

void solve () {
    int D, a, b, c, A, B, C;
    scanf("%d %d %d %d %d %d %d", &D, &a, &b, &c, &A, &B, &C);
    printf("%s\n", rec(D, a, b, c, A, B, C, 0) ? "yes" : "no");
}

int main () {
    int N;
    scanf("%d", &N);
    while (N--) {
        solve();
    }
}
