#include <iostream>
#include <string>
#include <cmath>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){
	int n;
	cin>>n;
	int ct=0;
	int m[9]={1,5,10,50,100,500,1000,5000,10000};
	for(int i=8;i>=0;i--){
		while(n/m[i]){
			ct++;
			n-=m[i];
		}
	}
	cout<<ct<<endl;
}

