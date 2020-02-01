//4 31
//11 13 24 7

#include <iostream>
typedef long long ll;
using namespace std;

int n,m,ans;

void solve(int N,int *val,int *sol,int sum,int ct){	
	
	if(sum==m){
		for(int i=0;i<ct;i++)
			cout<<sol[i]<<" ";
		cout<<endl;
		ans++;
		return;
	}
	else if(sum>m){
		return;
	}
	else if(N==n){
		return;
	}
	
	//¨ú
	sol[ct]=val[N];
	solve(N+1,val,sol,sum+val[N],ct+1);
	sol[ct]=0; 
	
	//¤£¨ú
	solve(N+1,val,sol,sum,ct);
	
	return; 
	
}
int main(){
	cin>>n>>m;
	const int MAXn = n;
	int val[MAXn];
	ans = 0;
	for(int i=0;i<MAXn;i++)
		cin>>val[i];
		
	int sol[MAXn];
	solve(0,val,sol,0,0);
	if(ans==0)
		cout<<"NO"<<endl;
}
