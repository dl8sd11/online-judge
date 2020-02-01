#include <iostream>
using namespace std;
int n;

void solve(int N,bool *usedNum,int *sol){
	if(N==n){
		for(int i=0;i<n;i++)
			cout<<sol[i];
		cout<<endl;
		return;
	}
	
	for(int i=1;i<=n;i++){
		if(!usedNum[i-1]){
			usedNum[i-1]=true;
			sol[N]=i;
			solve(N+1,usedNum,sol);
			usedNum[i-1]=false;
		}
	}
}
int main(){
	cin>>n;
	const int MAXn = n;
	
	bool usedNum[MAXn];
	int sol[MAXn];
	
	for(int i=0;i<MAXn;i++){
		usedNum[i] = false;
	}
	solve(0,usedNum,sol);
}

//AC
