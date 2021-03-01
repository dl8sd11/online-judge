#include <stdio.h>

struct node {
    int a;
    struct node* ptr;
}__attribute__((__packed__));

int main () {
    printf("%u",sizeof(struct node));
}
