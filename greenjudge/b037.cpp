#include <iostream>
using namespace std;
typedef long long ll;
ll n,m;

void backtrack(ll N,ll *sol){
	if(N==n){
		for(ll i=0;i<n;i++){
			cout<<sol[i];
		}
		cout<<endl;
		return;
	}
	for(ll i=0;i<=m;i++){
		sol[N]=i;
		backtrack(N+1,sol);
	}
	
}
int main(){
	
	cin>>n>>m;
	ll const MAX = n;
	ll sol[MAX];
	backtrack(0,sol);
} 
