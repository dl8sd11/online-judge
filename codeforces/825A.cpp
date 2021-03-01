#include<bits/stdc++.h>
#define REP(i,n) for(int i=0;i<n;i++)
#define pb push_back
typedef long long ll;
using namespace std;

int main(){
	int x;
	cin>>x;
	string a;
	cin>>a;
	int len_a = a.length();
	int ct = 0;
	for(int i=0;i<len_a;i++){
		if(a.at(i)=='0'){
			cout<<ct;
			ct=0;
		}	
		else{
			ct++;
		}		
	}
	if(a!="0")
		cout<<ct;
}

