#include "stdio.h"

int main () {
    int a[3] = {0};
    a[-1] = -1;
    printf("%d", a[-1] / 0);
}
