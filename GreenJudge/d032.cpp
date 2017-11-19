#include <iostream>
#include <string>
#include <cmath>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){
	int n;
	cin>>n;
	const int MAXn = n + 1;
	int a[MAXn];
	int coin[5]={1,5,10,25,50};
	for(int i=0;i<MAXn;i++)
		a[i]=0;
	a[0]=1;
	for(int j=0;j<5;j++){
		for(int i=0;i<MAXn;i++){
			int prev = 0;
			if(i-coin[j]>=0)
				prev = a[i-coin[j]];
			a[i] += prev;
		}	
	}
	cout<<a[MAXn-1];
	
	
}

