#include <iostream>
#include <string>
using namespace std;

int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		int m;
		cin>>m;
		string inp;
		cin>>inp;
		for(int j=0;j<inp.length();j++){
			char a;
			a=inp[j];
			if(a-'A'<m){
				cout<<char('Z'-(m-a+'A')+1);
			}
			else{
				cout<<char(a-m);
			}
		}
		cout<<endl;
	}
}
