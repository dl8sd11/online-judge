#include <iostream>
#include <string>
#include <cmath>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;
int n,a;
int act;
bool solve(int *c,int id){
	int p1=0,p2=0;
	for(int i=0;i<n;i++){
		if(c[id]==c[i])
			p1++;
		else if(c[i]==a)
			p2++;
		
		if(p2>p1)
			return false;
		if(p1>=act)
			return true;
	}
	return true;
}

int main(){
	act=0;
	cin>>n>>a;
	int c[n];
	
	REP(i,n){
		cin>>c[i];	
	}
	
	int firstA = -1;
	REP(i,n){
		if(c[i]==a){
			if(act==0)
				firstA = i;
			act++;
		}
	}
	if(firstA == -1){
		cout<<a+1;
		return 0;
	}
	if(firstA == 0){
		cout<<"-1"<<endl;
		return 0;
	}
	

	
	for(int i=0;i<firstA;i++){
		if(solve(c,i)){
			cout<<c[i]<<endl;
			return 0;
		}
	}
	
	cout<<"-1"<<endl;
	return 0;
		
	
}

