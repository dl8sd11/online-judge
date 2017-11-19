#include <iostream>
#include <string>
#include <cmath>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){
	int n;
	cin>>n;
	REP(i,n){
		string a;
		cin>>a;
		if(a.length()>10){
			cout<<a.at(0)<<a.length()-2<<a.at(a.length()-1)<<endl;
		}
		else{
			cout<<a<<endl;
		}	
	}
	
}

