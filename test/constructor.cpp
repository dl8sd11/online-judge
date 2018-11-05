#include <bits/stdc++.h>
using namespace std;
class test{
private:
  int a;
public:
  void foo(){
    a += 2;
  }
  void boo(){
    foo();
  }
  int get(){return a;}
};
int main(){
  test cry;
  cry.boo();
  cout<<cry.get()<<endl;
}
