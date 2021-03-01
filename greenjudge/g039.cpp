#include <iostream>
using namespace std;

int main(){
	int ct;
	cin>>ct;
	
	for(int i=0;i<ct;i++){
		int a,b,c;
		cin>>a>>b>>c;
		
		if(a==b||a==c||b==c)cout<<"NO"<<endl;
		else cout<<"YES"<<endl;
		
		
	}
}
