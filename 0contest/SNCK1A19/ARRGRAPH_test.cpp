#include <bits/stdc++.h>
using namespace std;


int main(){
  for(int i=2;i<=50;i++){
    for(int j=2;j<=50;j++){
      for(int k=2;k<=50;k++){
        for(int l=2;l<=50;l++){
          if(__gcd(i,j)==1&&__gcd(k,l)==1&&__gcd(i,l)!=1&&__gcd(k,i)!=1&&__gcd(k,j)!=1&&__gcd(j,l)!=1){
            cout<<"Found "<<i<<" "<<j<<" "<<k<<" "<<l<<endl;
          }
        }
      }
    }
  }
  cout<<"Done.\n";
}
