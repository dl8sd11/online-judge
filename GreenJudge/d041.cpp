#include <iostream>
#include <string>
#include <cmath>
#define REP(i,n) for(i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){
	string input;
	cin>>input;
	
	int ct=0;
	const int n=input.length();
	int i;
	REP(i,n){
		if(input.at(i)=='1')
			ct++;
		else if(input.at(i)!='0')
			break;
	}
	if(i==n)
		cout<<"�]�t1���ӼƬ�"<<ct<<endl;
	else
		cout<<input<<"�D�G�i���"<<endl;
}

