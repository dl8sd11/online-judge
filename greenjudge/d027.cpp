#include <iostream>
#include <string>
#include <cmath>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int toNum(char input){
	if(input<='9'){
		return input-'0';
	}
	else{
		return input-'A'+10;
	}
}
int main(){
	const int n=20;
	REP(i,n){
		string a;
		cin>>a;
		int sum=0;
		int digi = a.length();
		for(int j=0;j<digi;j++){
			sum+= toNum(a.at(j))*pow(16.0,digi-j-1);
		}
		cout<<sum<<endl;
		
	}
		
	
	
}

