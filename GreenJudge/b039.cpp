#include <iostream>
using namespace std;

int n;
int sol[12];
bool used[12][12]={};

void kill(int x,int y){
	used[x][y]=true;
	int tmpX=x;
	int tmpY=y;
	while(tmpX+1<n){
		tmpX+=1;
		used[tmpX][y]=true;
	}
	tmpX=x;
	while(tmpX-1>=0){
		tmpX-=1;
		used[tmpX][y]=true;
	}
	tmpY=y;
	while(tmpY+1<n){
		tmpY+=1;
		used[x][tmpY]=true;
	}
	
	while(tmpY-1>=0){
		tmpY-=1;
		used[x][tmpY]=true;
	}
	
	tmpX=x;
	tmpY=y;
	
	while(tmpX+1<n&&tmpY+1<n){
		tmpX++;
		tmpY++;
		used[tmpX][tmpY]=true;
	}
	
	tmpX=x;
	tmpY=y;
	
	while(tmpX-1>=0&&tmpY-1>=0){
		tmpX--;
		tmpY--;
		used[tmpX][tmpY]=true;
	}
	
	tmpX=x;
	tmpY=y;
	
	while(tmpX-1>=0&&tmpY+1<n){
		tmpX--;
		tmpY++;
		used[tmpX][tmpY]=true;
	}
	
	tmpX=x;
	tmpY=y;
	
	while(tmpX+1<n&&tmpY-1>=0){
		tmpY--;
		tmpX++;
		used[tmpX][tmpY]=true;
	}
	

}

void solve(int N){
	if(N==n){
		for(int i=0;i<n;i++){
			cout<<sol[i]+1<<" ";
		}
		cout<<endl;
		return;
	}
	
	for(int i=0;i<n;i++){
		if(!used[i][N]){
			bool prev[12][12];
			for(int k=0;k<12;k++){
				for(int j=0;j<12;j++){
					prev[k][j]=used[k][j];
				}
			}
			kill(i,N);
			sol[N]=i;
			solve(N+1);
			
			for(int k=0;k<12;k++){
				for(int j=0;j<12;j++){
					used[k][j]=prev[k][j];
				}
			}
			
			
		}
	}
	
	
}

int main(){
	cin>>n;
	solve(0);
} 

//AC
