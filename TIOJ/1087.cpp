#ifdef tmd
#include <iostream>
#else
#include "lib1087.h"
#endif
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)

int st[6] = {10, 15, 20};

int win[31][31][31];

#ifdef tmd
void Initialize() {
}
void Take_Stone(int a, int b, int *c, int *d){
}
#endif

/*********************GoodLuck***********************/
int main () {
    Initialize();

    REP (i, st[0]+1) {
        REP (j, st[1]+1) {
            REP (k, st[2]+1) {
                if (i + j + k == 0) {
                    win[i][j][k] = true;
                } else {
                    REP1 (l, i) {
                        win[i][j][k] |= !win[i-l][j][k];
                    }
                    REP1 (l, j) {
                        win[i][j][k] |= !win[i][j-l][k];
                    }
                    REP1 (l, k) {
                        win[i][j][k] |= !win[i][j][k-l];
                    }
                }
            }
        }
    }

    #ifdef tmd
    std::cout << win[10][15][20] << std::endl;
    #endif

    while (st[0] + st[1] + st[2] > 0) {
        int i = st[0], j = st[1], k = st[2];
        int p = -1, d = -1;
        REP1 (l, i) {
            if (!win[i-l][j][k]) {
                p = 0, d = l;
            }
        }
        REP1 (l, j) {
            if (!win[i][j-l][k]) {
                p = 1, d = l;
            }
        }
        REP1 (l, k) {
            if (!win[i][j][k-l]) {
                p = 2, d = l;
            }
        }
        while (p < 0);
        st[p] -= d;



        int rp, rn;
        Take_Stone(p+1, d, &rp, &rn);

        while (rp < 1);

        st[rp-1] -= rn;

    }
}
