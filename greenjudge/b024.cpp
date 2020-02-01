#include <iostream>
using namespace std;
long long unsigned int step(int n){
	static long long unsigned int dp[91]={};
	if(dp[n]==0){
		if(n==2)return 2;
		else if(n==1)return 1;
		else{
			dp[n]=step(n-1)+step(n-2);
			return dp[n];
		} 
	}
	else return dp[n];
	
}
int main(){
	int n;
	cin>>n;
	
	long long unsigned int k=step(n);
	cout<<k<<" "<<step(k%n);
}
