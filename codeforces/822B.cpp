#include <iostream>
#include <string>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){
	int n,m;
	string s,l;
	cin>>n>>m>>s>>l;
	int maxNum = -1;
	int maxId = -1;
	for(int i=0;i<m-n+1;i++){
		int sum = 0;
		for(int j=0;j<n;j++){
			if(s[j]==l[i+j]){
				sum++;
			}
		}
		if(sum>maxNum){
			maxNum = sum;
			maxId = i;
		}
	}
	cout<<n-maxNum<<endl;
	for(int j=0;j<n;j++){
			if(s[j]!=l[maxId+j]){
				cout<<j+1<<" ";
			}
		}
}

