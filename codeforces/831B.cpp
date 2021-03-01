#include<bits/stdc++.h>
#define REP(i,n) for(int i=0;i<n;i++)
#define pb push_back
typedef long long ll;
using namespace std;

int main(){
	pair<char,char> a[26];
	
	string c;
	for(int i=0;i<26;i++){
		cin>>a[i].first;
	}
	
	for(int i=0;i<26;i++){
		cin>>a[i].second;
	}
	
	cin>>c;
	sort(a,a+26);
	
	int len_C = c.length();
	for(int i=0;i<len_C;i++){
		if(c[i]>'Z'){
			int alpha = c[i]-'a';
			cout<<a[alpha].second;
		}
		else if(c[i]>='A'){
			int alpha = c[i]-'A';
			cout<<char(a[alpha].second-('a'-'A'));
		}
		else{
			cout<<c[i];
		}
	}
}

