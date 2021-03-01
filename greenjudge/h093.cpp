#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){
	int n;
	cin>>n;
	REP(i,n){
		double a,b;
		cin>>a>>b;
		double ans;
		ans = 1-(a/b)*(a/b);
		cout<<fixed<<setprecision(3)<<ans<<endl;
	}
}

