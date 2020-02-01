#include <iostream>
using namespace std;

int main(){
	int a,b;
	cin>>a>>b;
	while(a!=0||b!=0){
		if(a%2==b%2)cout<<"Win"<<endl;
		else cout<<"Loss"<<endl;
		cin>>a>>b;
	}
}
