#include <iostream>
typedef long long ll;
typedef double lf;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
using namespace std;

int main(){
	int n,m;
	cin>>n>>m;
	const int MAXn = n+1;
	bool a[MAXn];
	
	for(int i=0;i<MAXn;i++)a[i]=0;
	int mt = m;
	int ct=0;
	m=0;
	
	int shift = 0;
		while(shift<=mt-1){
			while(1){
				m++;
				if(m>n)m=1;
				if(a[m]==0)break;
			}
			shift++;
		}
		
	while(ct<n-1){
		
		a[m]=1;
		
		shift = 0;
		while(shift<=mt-1){
			while(1){
				m++;
				if(m>n)m=1;
				if(a[m]==0)break;
			}
			shift++;
		}
		ct++;
	}
	REP1(i,n)if(a[i]==0)cout<<i;
	
}

//AC

