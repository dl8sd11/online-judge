#include <iostream>
#include <string>
using namespace std;

int main(){
	string a,b;
	cin>>a>>b;
	
	const int maxA = a.length();
	const int maxB = b.length();
	
	int ans[maxA+1][maxB+1];
	for(int i=0;i<=maxA;i++){
		ans[i][0]=0;
	}
	for(int i=0;i<=maxB;i++){
		ans[0][i]=0;
	}
	
	for(int i=0;i<maxA;i++){
		for(int j=0;j<maxB;j++){
			if(a[i]==b[j])ans[i+1][j+1]=ans[i][j]+1;
			else{
				if(ans[i][j+1]>ans[i+1][j])ans[i+1][j+1]=ans[i][j+1];
				else ans[i+1][j+1]=ans[i+1][j];
			}	
		}
	}
	
	
//	for(int i=0;i<=maxA;i++){
//		for(int j=0;j<=maxB;j++){
//			cout<<ans[i][j]<<" ";
//		}
//		cout<<endl;
//	}	
	cout<<ans[maxA][maxB];
}


//AC ><
