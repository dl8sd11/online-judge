#include <iostream>
#include <string>
#include <cmath>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){
	int n,k;
	cin>>n>>k;
	int a[n];
	int sum=0;
	REP(i,n){
		cin>>a[i];
		sum+=a[i];
	}
		
	int ct = 0;
	while(round((sum+ct*k)/(ct+n+0.0))<k){
		ct++;
	}
	cout<<ct;
}

