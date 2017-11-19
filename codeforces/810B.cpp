#include<bits/stdc++.h>
#define REP(i,n) for(ll i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){
	ll n,f;
	cin>>n>>f;
	ll k[n],l[n],a[n];
	REP(i,n){
		cin>>k[i]>>l[i];
		a[i] = min(l[i],k[i]*2) - min(k[i],l[i]);
	}
	sort(a,a+n);
	
	ll sum = 0;
	REP(i,n){
		sum += min(l[i],k[i]);
	}
	
	for(ll i=n-1;i>=n-f;i--){
		sum += a[i];
	}
	
	cout<<sum<<endl;
	
		
}

