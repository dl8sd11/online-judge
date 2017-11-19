#include <iostream>
using namespace std;

int main(){
	int m,n;
	cin>>m>>n;
	
	const int yMAX = m+1;
	const int xMAX =n+1;
	int map[xMAX][yMAX];
	
	for(int i=0;i<xMAX;i++)map[i][0]=1;
	for(int i=0;i<yMAX;i++)map[0][i]=1;
	
	for(int i=1;i<yMAX;i++){
		for(int j=1;j<xMAX;j++){
			cin>>map[j][i];
		}
	}
	
	
	int c[xMAX][yMAX];
	for(int i=0;i<yMAX;i++){
		for(int j=0;j<xMAX;j++){
			if(map[i][j]==1)c[i][j]=0;
			else{
				if(map[i][j-1]+map[i-1][j]==0)c[i][j]=c[i-1][j-1]+1;
				else c[i][j]=1;
			}
				
		}
	}
	
	int ans=0;
	for(int i=0;i<yMAX;i++){
		for(int j=0;j<xMAX;j++){
			if(c[i][j]>ans)ans=c[i][j];
		}
	}
	cout<<ans*ans<<endl;
}
