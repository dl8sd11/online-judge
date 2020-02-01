#include <iostream>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){
	int n;
	cin>>n;
	while(n!=0){
	
		ll sum = 0;	
		REP(i,n){
			ll tmp;
			cin>>tmp;
			sum+=tmp*tmp;
		}
		cout<<sum<<endl;
		
		cin>>n;
	}
}

