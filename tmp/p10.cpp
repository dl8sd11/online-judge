#include <stdio.h>
int main(){
  union data{
    int a;
    char b;
  }test;
  test.a = 17;
  test.b = 20;
  printf("%d,%d\n",test.a,test.b);
}
