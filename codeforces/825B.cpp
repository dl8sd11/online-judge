#include<bits/stdc++.h>
#define REP(i,n) for(int i=0;i<n;i++)
#define pb push_back
typedef long long ll;
using namespace std;

int main(){
	char a[10][10];
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			cin>>a[j][i];
		}
	}
	
	bool flag = false;
	for(int j=0;j<10;j++){
		for(int i=0;i<10;i++){
			if(a[i][j]=='.'){
				int ti = i;
				int tj = j;
				int horizontal = 0;
				
				while(ti+1<10&&a[ti+1][tj]=='X'){
					ti++;
					horizontal++;
				}
				ti = i;
				while(ti-1>=0&&a[ti-1][tj]=='X'){
					ti--;
					horizontal++;
				}
				if(horizontal>=4)
					flag = true;
				
				
				int vertical = 0;
				ti = i;
				tj = j;
				while(tj+1<10&&a[ti][tj+1]=='X'){
					tj++;
					vertical++;
				}
				tj = j;
				while(tj-1>=0&&a[ti][tj-1]=='X'){
					tj--;
					vertical++;
				}
				if(vertical>=4)
					flag = true;
					
				int diagonal = 0;
				ti = i;
				tj = j;
				while(ti+1<10&&tj+1<10&&a[ti+1][tj+1]=='X'){
					tj++;
					ti++;
					diagonal++;
				}
				ti = i;
				tj = j;
				while(tj-1>=0&&ti-1>=0&&a[ti-1][tj-1]=='X'){
					tj--;
					ti--;
					diagonal++;
				}
				if(diagonal>=4)
					flag = true;
					
				diagonal = 0;
				ti = i;
				tj = j;
				while(ti-1>=0&&tj+1<10&&a[ti-1][tj+1]=='X'){
					tj++;
					ti--;
					diagonal++;
				}
				
				
				ti = i;
				tj = j;
				while(ti+1<10&&tj-1>=0&&a[ti+1][tj-1]=='X'){
					tj--;
					ti++;
					
					diagonal++;
				}
				if(diagonal>=4){
					
					flag = true;	
				}
				
				
			}
		}
	}
	
	if(flag)
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;
}

