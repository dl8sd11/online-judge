#include <iostream>
using namespace std;
long long int solve(int x,int y){
	const int xMAX = x+1;
	const int yMAX = y+1;
	long long int map[xMAX][yMAX];
	for(int i=0;i<=x;i++){
		for(int j=0;j<=y;j++){
			if(i==0||j==0)map[i][j]=1;
			else map[i][j]=map[i-1][j]+map[i][j-1];
		}
	}
	return map[x][y];
}
int main(){
	int x,y;
	cin>>x>>y;
	
	cout<<solve(x,y);
}
