#include<bits/stdc++.h>
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP(i,k) for(ll i=0;i<k;i++)
typedef long long ll;
using namespace std;

int main(){
	ll n,k,p;
	cin>>n>>k>>p;
	
	ll a[n];
	REP(i,n)
		cin>>a[i];
	
	ll b[k];
	
	REP(i,k){
		cin>>b[i];		
	}
	
	sort(a,a+n);
	sort(b,b+n)
	
	
	ll maxDis = 0;
	
	cout<<maxDis<<endl;
	
	
	
	
}

