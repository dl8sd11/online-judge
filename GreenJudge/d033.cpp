#include <iostream>
#include <string>
#include <cmath>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){
	string input;
	while(cin>>input){
		
		int flag = true;
		while(input!=""){
			if(input.length()==1){
				flag = false;
				break;
			}
			char begin = input.at(0);
			char last = input.at(input.length()-1);
			if(begin=='('&&last==')');
			else if(begin=='['&&last==']');
			else if(begin==')'&&last=='(');
			else if(begin==']'&&last=='[');
			else{
				flag = false;
				break;
			}
			input = input.substr(1,input.length()-2);
		}
		if(flag){
			cout<<"Correct"<<endl;
		}
		else{
			cout<<"Error"<<endl;
		}
	}
}

