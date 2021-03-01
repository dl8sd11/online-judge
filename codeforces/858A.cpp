#include <iostream>
using namespace std;

int main(){
  long long int  n,k;
  cin>>n>>k;

  int two = 0;
  int five = 0;
  int zero = 0;

  int tmpn=n;
  while(tmpn%10==0){
    tmpn=tmpn/10;
    zero++;
  }
  while(tmpn%2==0){
    tmpn=tmpn>>1;
    two++;
  }
  while(tmpn%5==0){
    tmpn=tmpn/5;
    five++;
  }

  int delta = k-zero;
  if(delta>0){
    if(two>0){
      for(int i=0;i<two;i++){
        n*=5;
        delta--;
        if(delta==0)break;
      }



    }
    else if(five>0){
      for(int i=0;i<five;i++)
        {
          n*=2;
          delta--;
          if(delta==0)break;
        }

    }
  }

  cout<<n;
  for(int i=0;i<delta;i++){
    cout<<"0";
  }
  cout<<endl;
}
