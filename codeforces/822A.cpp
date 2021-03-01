#include <iostream>
#include <string>
#include <cmath>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){
	ll a,b;
	cin>>a>>b;
	a= min(a,b);
	ll ans =1;
	for(int i=1;i<=a;i++){
		ans *= i;
	}
	cout<<ans<<endl;
}

