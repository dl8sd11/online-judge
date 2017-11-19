#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;
bool func(int i,int j){return i>j;}

int main(){
	int sofaCt;
	cin>>sofaCt;
	int n,m;
	cin>>n>>m;
	int pos[sofaCt][4];
	for(int i=0;i<sofaCt;i++){
		int x1,x2,y1,y2;
		cin>>x1>>y1>>x2>>y2;
		pos[i][0]=min(x1,x2);
		pos[i][1]=max(x1,x2);
		pos[i][2]=min(y1,y2);
		pos[i][3]=max(y1,y2);
	}
	int ans[sofaCt]={};
	int cn[4];
	int flag = false;
	for(int i=0;i<4;i++){
		cin>>cn[i];
	}
	
	for(int j=0;j<4;j++){
		int tmp[sofaCt];
		int search;
		for(int i=0;i<sofaCt;i++){
			tmp[i] = pos[i][j];
		}
		if(j%2==0){
			sort(tmp,tmp+sofaCt);
		}
		else{
			sort(tmp,tmp+sofaCt,func);
		}
		
		if(tmp[cn[j]-1]==tmp[cn[j]]){
			if(tmp[cn[j]]==tmp[cn[j]+1])
				flag = true;
			else
				search = tmp[cn[j]];
		}
		else{
			search = tmp[cn[j]];
		}
		
		for(int i=0;i<sofaCt;i++){
			if(pos[i][j]==search){
				ans[i]++;
			}
		}
	}
	
	if(flag){
		cout<<"-1"<<endl;
		return 0;
	}
	for(int i=0;i<sofaCt;i++){
		if(ans[i]==4)
		{
			cout<<i+1<<endl;
			return 0;
		}
	}
	cout<<"-1"<<endl;
}

