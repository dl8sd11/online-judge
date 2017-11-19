#include <iostream>
#include <string>
using namespace std;

int main(){
	string line;
	getline(cin,line);
	//a65 A97
	//z90 Z122

	int ct[26]={};
	
//	for(int i=0;i<line.length();i++){
//		if(line[i]==i+64||line[i]==i+96){
//			ct[i-1]++;
//		}
//	}
//		
	for(int i=1;i<=26;i++){
		for(int j=0;j<line.length();j++){
			if(line[j]==static_cast<char>(i+64)||line[j]==static_cast<char>(i+96)){
				ct[i-1]++;
			}
		}
		
	}
	for(int i=1;i<=26;i++){
		char tmp = i+64;
		cout<<tmp<<" ";
	}
	cout<<endl;
	for(int i=1;i<=26;i++){
		cout<<ct[i-1]<<" ";
	}
}
