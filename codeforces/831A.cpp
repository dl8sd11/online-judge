#include<bits/stdc++.h>
#define REP(i,n) for(int i=0;i<n;i++)
#define pb push_back
typedef long long ll;
using namespace std;

int main(){
	int n;
	cin>>n;
	int a[n];
	REP(i,n)
		cin>>a[i];
	
	bool flag = false;
	bool increasing = false;
	bool constant = false;
	bool decreasing = false;
	for(int i=1;i<n; i++){
		if(a[i]-a[i-1]>0){
			if(constant || decreasing){
				flag = true;
				break;
			}
			else{
				increasing = true;
			}
		}
		else if(a[i]-a[i-1] == 0){
			if(decreasing){
				flag = true;
				break;
			}
			else{
				constant = true;
			}
		}
		else{
			decreasing = true;
		}
	}
	
	if(flag){
		cout<<"NO"<<endl;
	}
	else{
		cout<<"YES"<<endl;
	}
}

