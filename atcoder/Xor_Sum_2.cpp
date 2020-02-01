#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MAXN = 2e5 + 3;
ll n,a[MAXN], spre[MAXN], xpre[MAXN];

int main(){
	cin>>n;
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		spre[i] = a[i] + spre[i-1];
		xpre[i] = a[i]^xpre[i-1];
	}

	ll ans = 0;
	for(ll i=1;i<=n;i++){
		ll l = i,r = n + 1;
		while(l<r-1){
			ll mid = (l+r)/2;
			if((spre[mid]-spre[i-1]) == (xpre[mid]^xpre[i-1]))l=mid;
			else r=mid;
		}

		ans += l-i+1;
	}

	cout<<ans<<endl;
}