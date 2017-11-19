#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#define REP(i,n) for(int i=0;i<n;i++)
#define BIGNUM 1e7+5
typedef long long ll;
using namespace std;

int main(){
	int n;
	cin>>n;
	const int MAX = n;
	int a[MAX];
	ll sum =0;
	REP(i,n)
		cin>>a[i];
	for(int i=1; i<n; i++){
		sort(a,a+n);
		int add = a[0] + a[1];
		sum += add;
		a[0] = add;
		a[1] = BIGNUM;
	}
	cout<<sum<<endl;
}

