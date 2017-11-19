#include <iostream>
#include <string>
#include <cmath>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){
	int  n,k;
	cin>>n>>k;
	int a[n];
	k--;
	REP(i,n){
		cin>>a[i];
	}
	
	if(a[k]==0){
		int sum=0;
		for(int i=0;i<k;i++){
			if(a[i])sum++;
		}
		cout<<sum<<endl;
		return 0;
	}	
	else{
		while(a[k+1]==a[k])
		{
			k++;
		}
	}
	cout<<k+1<<endl;
	
	
	
}

