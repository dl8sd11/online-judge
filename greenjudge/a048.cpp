#include <iostream>
typedef long long ll;
using namespace std;

int main(){
	ll n;
	cin>>n;
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=n-i;j++){
			cout<<'_';
		}
		for(ll j=1;j<=i*2-1;j++){
			cout<<i;
		}
		cout<<endl;
	}
}

