#include <iostream>
#include <string>
#define FOR(a,b,c,d) for(int a=b;a<c;a+=d)
#define REP(i,n) FOR(i,0,n,1)

using namespace std;

int main(){
  string a,b;
  cin>>a>>b;
  int alen = a.length();
  int blen = b.length();

  for(int i=min(alen,blen)+1;i>=0;i--){
    bool flag = false;
    REP(j,i){
      int bst = blen-i;
      if(a[j]!=b[bst+j])
      {

        flag = true;
        break;
      }
    }
    if(!flag){
      cout<<i<<endl;
      break;
    }
  }
}
