#include <stdio.h>

#define TEST ({int a=3;a;})

int main () {
    int a = {1;2};
    printf("%d", a);
}
