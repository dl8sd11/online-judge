#include <iostream>
using namespace std;
int count=0;
int solve(int n,int max){
	if(n<0)return 0;
	if(n==0)return 1;
	static int pz[5]={2,5,10,20,25};
	int sum=0;
	for(int i=0;i<5;i++){
		if(pz[i]>max)continue;
		sum+=solve(n-pz[i],pz[i]);
	}	
	return sum;
}
int main(){
	int n;
	cin>>n;
	
	cout<<solve(n,100)<<endl;
	
}
