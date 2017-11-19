//b030 ­I¥]°ÝÃD 
#include <iostream>
using namespace std;
int solve(int ls[][2],int max,int m,int lg, int dp[][1001]){
	 
	if(m<0)return -10000;
	if(m==0)return 0;
	if(dp[lg][m]!=0)return dp[lg][m];
	int maxLike = 0;
	for(int i=0;i<max;i++){
		if(lg>i){
			int like = solve(ls,max,m-ls[i][0],i,dp) + ls[i][1];
			if(maxLike<like){
				maxLike=like;
			}	
		}		
	}
	dp[lg][m]=maxLike;
	return maxLike;
}
int main(){
	int n,m;
	cin>>n>>m;
	
	const int max= n;
	int ls[max][2];
	int dp[max+1][1001];
	for(int i=0 ;i<1001;i++){
		for(int j=0;j<=max;j++){
			dp[j][i]=0;
		}
	}
	for(int i=0;i<max;i++){
		cin>>ls[i][0]>>ls[i][1];
	}
	
	cout<<solve(ls,max,m,max,dp);
}

//AC
