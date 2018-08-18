#include <bits/stdc++.h>
using namespace std;

void foo(int *a){
  *a = 4;
}
void boo(int *&a){

  *a = 4;
}

int main(){
  int b = 2;
  int *a = &b;
  foo(a);
  cout<<b<<endl;


  boo(a);
  cout<<b<<endl;
}
