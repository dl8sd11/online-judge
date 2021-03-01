#include <stdio.h>

void swap_val (int x, int y) {
    int tmp = x;
    x = y;
    y = tmp;
}

void swap_ptr (int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void swap_ref (int &x, int &y) {
    int tmp = x;
    x = y;
    y = tmp;
}

int main () {
    int x = 3, y = 5;
    printf("%d %d\n", x, y);

    swap_val(x, y);
    printf("%d %d\n", x, y);

    swap_ptr(&x, &y);
    printf("%d %d\n", x, y);

    swap_ref(x, y);
    printf("%d %d\n", x, y);

}
