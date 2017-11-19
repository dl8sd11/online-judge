#include <iostream>
#include <cmath>
#define REP(j,n) for(int j=0;j<n;j++)
typedef long long ll;
using namespace std;

bool primeTest(int N){
	int N_sqrt = sqrt(N);
	if(N%2==0 or N%3==0){
		return false;
	}
	for(int i=5, step=2;i<=N_sqrt;i+=step,step = 6-step){
		if(N%i==0&&N/i!=1){
			return false;
		}
	}
	return true;
}
int main(){
	int n;
	cin>>n;
	REP(j,n){
		int a,b;
		int sum = 0;
		cin>>a>>b;
		for(int i=a;i<=b;i++){
			
			if( i!=2 && i!=3){
				if(i==1){
					sum+=1;
				}
				else if(!primeTest(i)){
					sum+=i;
				}
			}
		}
		cout<<sum<<endl;
	}
}

