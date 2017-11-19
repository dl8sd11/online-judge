#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){

	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		int m;
		cin>>m;
		const int MAX = m;
		int a[MAX];
		int gcd;
		for(int j=0;j<m;j++){
			cin>>a[j];
			if(j==0){
				gcd=a[j];
			}
			else{
				gcd=__gcd(gcd,a[j]);
			}
		}
		cout<<gcd<<endl;
	}
}

