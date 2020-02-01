#include <iostream>
using namespace std;

int main(){
	int m,n;
	cin>>m>>n;
	
	const int xMAX = m;
	const int yMAX =n;
	int map[xMAX][yMAX];
	
	for(int i=0;i<xMAX;i++){
		for(int j=0;j<yMAX;j++){
			cin>>map[i][j];
		}
	}
	
	int maxV=0;
	for(int i=0;i<xMAX;i++){
		for(int j=0;j<yMAX;j++){
			for(int k=i;k<xMAX;k++){
				for(int l=j;l<yMAX;l++){
					//st[i][j] ed[k][l]
					
					int sum=0;
					for(int a=i;a<=k;a++){
						for(int b=j;b<=l;b++){
							sum+=map[a][b];
						}
					}
					if(sum==0){
						int now = (k-i+1)*(l-j+1);
						if(now>maxV)maxV=now;
					}
					
				}
			}			
		} 	
	}
	cout<<maxV;
}
