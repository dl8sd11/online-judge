//b030 ­I¥]°ÝÃD 
#include <iostream>
using namespace std;
int solve(int ls[][2],int max,int m){
	static int dp[1001]={};
	if(m<0)return -10000;
	if(m==0)return 0;
	if(dp[m]!=0)return dp[m];
	int maxLike = 0;
	for(int i=0;i<max;i++){
		int like = solve(ls,max,m-ls[i][0]) + ls[i][1];
		if(maxLike<like)maxLike=like;
	}
	dp[m]=maxLike;
	return maxLike;
}
int main(){
	int n,m;
	cin>>n>>m;
	
	const int max= n;
	int ls[max][2];
	
	for(int i=0;i<max;i++){
		cin>>ls[i][0]>>ls[i][1];
	}
	
	cout<<solve(ls,max,m);
}

//AC
