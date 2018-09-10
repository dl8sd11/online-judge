#include "lib1904.h"
bool solve(int n,int a[]){
  int sum = 0;
  int t = 1;
  REP(i,n)sum+=t*a[i],t*=880301,sum;
  return true;
}
