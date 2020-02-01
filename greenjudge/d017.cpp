#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int compare(int i,int j){
	return (i>j);
}
int main(){
	string input;
	cin>>input;
	
	const int n= input.length();
	int a[n];
	REP(i,n){
		a[i]=input.at(i)-'0';
	}
	sort(a,a+n,compare);
	REP(i,n)cout<<a[i];
}

