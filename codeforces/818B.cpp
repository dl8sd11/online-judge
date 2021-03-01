#include <iostream>
#include <string>
#include <cmath>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){
	int n,m;
	cin>>n>>m;
	bool a[n] ={};
	int ans[n]={};
	int prevIn;
	cin>>prevIn;
	bool flag = false;
	for(int i=1;i<m;i++){
		int nowIn;
		cin>>nowIn;
		int val = (nowIn+n-prevIn-1)%n+1;
		if(a[val-1]){
			int target = (ans[prevIn-1]+prevIn-1)%n+1;
			if(target==nowIn){
				prevIn = nowIn;
				continue;
			}
			flag = true;
			break;
		}
		if(ans[prevIn-1]!=0)
			flag = true;
		a[val-1]=true;
		ans[prevIn-1] = val;
		prevIn = nowIn;		
	}
	if(flag){
		cout<<"-1"<<endl;
		return 0;
	}
	REP(i,n){
		if(ans[i]==0){
			for(int j=0;j<n;j++){
				if(!a[j]){
					a[j] = true;
					ans[i] = j+1;
					break;
				}
			}
			
		}
		cout<<ans[i]<<" ";
	}
	cout<<endl;
		
}

