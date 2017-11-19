#include<bits/stdc++.h>
#define REP(i,n) for(int i=0;i<n;i++)
#define pb push_back
typedef long long ll;
using namespace std;
bool palindrome(int h,int m){
	if(h/10==m%10&&h%10==m/10){
		return true;
	}
	else{
		return false;
	}
}

int main(){
	int h;
	int m;
	string input;
	cin>>input;
	stringstream ss;
	ss<<input.substr(0,2);
	ss>>h;
	stringstream ss2;
	ss2<<input.substr(3,2);
	ss2>>m;
	
	int ct = 0;
	while(!palindrome(h,m)){
		m+=1;
		if(m==60){
			m=0;
			h++;
			if(h==24){
				h=0;
			}
		}
		ct++;
	}
	cout<<ct<<endl;
}

