#include <iostream>
using namespace std;

int main(){
	int n,k;
	cin>>n>>k;
	
	if(n==k)
		cout<<0<<' ';
	else if(k==0)
		cout<<0<<' ';
	else
		cout<<1<<' ';
	
	int room = n/3;
	
	
	if(room>=k)
		cout<<k*2<<endl;
	else
	{
		int lef =  n - room*3;
		if(k-room==1&&lef==2)
			cout<<room*2+1;
		else
			cout<<room*2-(k-room-lef)<<endl;
	}
}
