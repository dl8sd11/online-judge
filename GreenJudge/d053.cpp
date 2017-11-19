#include <iostream>
#include <string>
#include <cmath>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

long input;
void solve(int num,int now){
	bool flag = 0;
	for(int k=3;k<=sqrt(input);k+=2){
		if(num%k==0)
		{
			flag = 1;
			break;
		}
	}
	if(num%2==0)
		flag=1;
	if(num==1){
		return;
	}
	if(!flag){
		cout<<" * "<<num;
		return;
	}
	while(num%now==0){
		num/=now;
		cout<<" * "<<now;
	}
	solve(num,now+1);
}
int main(){
	
	cin>>input;
	
	cout<<input<<" = ";
	int i;
	for(i=2;i<=input;i++){
		if(input%i==0)
			break;
	}
	cout<<i;
	solve(input/i,i);
	
}

