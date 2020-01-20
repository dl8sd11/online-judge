#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int maxnut, *x;
int pos = 0, n;
int CalcThemaxnut();
int main() {
    if (x == NULL) x = (int*)malloc(1010 * sizeof (int));
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; ++ i) {
            while (scanf("%d", &x[pos ++]) == 1) {
                maxnut = 0;
                CalcThemaxnut();
                break;
            }
        }
        break;
    }
    printf("%d\n", maxnut);
    exit(0);
}

int CalcThemaxnut() {
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < pos; ++ i) {
        maxnut += x[i];
        assert(cnt1 == i); 
        assert(cnt2 == i); 
        cnt1 += 1;
        cnt2 += 1;
    }
    assert(cnt1 == pos); 
    assert(cnt2 == pos);
    return maxnut;
}