#include <iostream>
#include <string>
#include <cmath>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){
	ll n,k;
	cin>>n>>k;
	
	ll i = floor((n/2.0)/(k+1));
	
	cout<<i<<" "<<i*k<<" "<<n-i-i*k<<endl;
}

