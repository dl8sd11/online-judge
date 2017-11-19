#include <iostream>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){
ll n;
cin>>n;
REP(i,n){
	ll m;
	cin>>m;
	ll prev;
	cin>>prev;
	ll max = 0;
	ll maxIdx = 1;
	for(int j=1;j<m;j++){
		int now;
		cin>>now;
		if(now-prev>max){
			maxIdx = j;
			max = now-prev;
		}
		prev = now;
	}
	cout<<maxIdx<<endl;
}
}

