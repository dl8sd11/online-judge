#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		int a,b;
		cin>>a>>b;
		int mcm = (a*b)/__gcd(a,b);
		cout<<mcm<<endl;
	}
}
