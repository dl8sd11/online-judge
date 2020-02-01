#include <bits/stdc++.h>
using namespace std;

int n,m;
char c;
int color[103][103];
int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++)for(int j=0;j<m;j++)cin>>c,color[i][j] = (c=='.'?0:1);

	for(int i=0;i<n;i++){
		bool flag = 1;
		for(int j=0;j<m;j++){
			if(color[i][j]==1){
				flag = 0;
				break;
			}
		}
		if(flag){
			for(int j=0;j<m;j++){
				color[i][j] = -1;
			}
		}
	}

	for(int j=0;j<m;j++){
		bool flag = 1;
		for(int i=0;i<n;i++){
			if(color[i][j]==1){
				flag = 0;
				break;
			}
		}
		if(flag){
			for(int i=0;i<n;i++){
				color[i][j] = -1;
			}
		}
	}

	for(int i=0;i<n;i++){
		bool flag = 0;
		for(int j=0;j<m;j++){
			if(color[i][j]!=-1){
				cout<<(color[i][j]?'#':'.');
				flag = 1;
			}
		}
		if(flag)cout<<endl;
	}
}