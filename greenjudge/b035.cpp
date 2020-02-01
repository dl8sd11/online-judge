#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){
	int n;
	cin>>n;
	const int MAX = n;
	int t[MAX];
	REP(i,n){
		cin>>t[i];
	}
	sort(t,t+n);
	ll sum=0;
	for(int i=0;i<n;i++){
		sum += (n-i-1) * t[i];
	}
	cout<<sum*100<<endl;
}

