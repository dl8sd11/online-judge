#include <iostream>
#include <string>
using namespace std;

int main(){
	int ct;
	cin>>ct;
	
	for(int j=0;j<ct;j++){
		string t;
		cin>>t;
		int i;
		for(i=0;i<t.length();i++){
			if(t[i]!=t[t.length()-i-1])break;
		}
		if(i==t.length())cout<<"yes"<<endl;
		else cout<<"no"<<endl;
	}
}

//ac
