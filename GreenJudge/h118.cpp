#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define REP(i,n) for(int i=0;i<n;i++)
#define pb push_back
typedef long long ll;
using namespace std;

bool binaryFind(ll *data,ll search,ll n)
{
	ll low=0;
	ll high = n-1;
	while(low<=high){
		ll mid = (low+high)/2;
		if(data[mid]==search){
			return true;
		}
		else if(data[mid]>search){
			high = mid-1;
		}
		else{
			low = mid + 1;
		}
	}
	return false;
}
int main(){
	ll n;
	cin>>n;
	REP(i,n){
		ll m;
		cin>>m;
		const ll MAXn = m;
		ll eat[MAXn];
		for(ll j=0;j<m;j++){
			cin>>eat[j];
			if(binaryFind(eat,eat[j],j)){
				if(binaryFind(eat,eat[j]*2,j)){
					m--;
					j--;
				}
				else{
					eat[j]*=2;
					sort(eat,eat+j);
				}
			}
			else{
				sort(eat,eat+j);
			}
			
		}
		
		cout<<m<<endl;
		

	}
}

