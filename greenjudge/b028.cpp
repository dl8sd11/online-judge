#include <iostream>
using namespace std;
int solve(int n,int t,int m){
	static int ch[6]={1,5,10,12,16,20};
	if(n<0)return 200;
	if(n==0)return 0;
	if(m>=20){
		int sol[6];
		for(int i=0;i<6;i++){
			sol[i]=solve(n-ch[i],t,ch[i]);
		}		
		int min = 287;
		int idx=6;
		for(int i=0;i<6;i++){
			if(sol[i]<min){
				min=sol[i];
				idx = i;
			}
		}
		
		return t+1+min;
		
	}
	else if(m>=16){
		int sol[5];
		for(int i=0;i<5;i++){
			sol[i]=solve(n-ch[i],t,ch[i]);
		}		
		int min = 200;
		int idx=6;
		for(int i=0;i<5;i++){
			if(sol[i]<min){
				min=sol[i];
				idx = i;
			}
		}
		return t+1+min;
	}
	else if(m>=12){
		int sol[4];
		for(int i=0;i<4;i++){
			sol[i]=solve(n-ch[i],t,ch[i]);
		}		
		int min = 200;
		int idx=6;
		for(int i=0;i<4;i++){
			if(sol[i]<min){
				min=sol[i];
				idx = i;
			}
		}
		return t+1+min;
	}
	else if(m>=10){
		int sol[3];
		for(int i=0;i<3;i++){
			sol[i]=solve(n-ch[i],t,ch[i]);
		}		
		int min = 200;
		int idx=6;
		for(int i=0;i<3;i++){
			if(sol[i]<min){
				min=sol[i];
				idx = i;
			}
		}
		return t+1+min;
	}
	else if(m>=5){
		int sol[2];
		for(int i=0;i<2;i++){
			sol[i]=solve(n-ch[i],t,ch[i]);
		}		
		int min = 200;
		int idx=6;
		for(int i=0;i<2;i++){
			if(sol[i]<min){
				min=sol[i];
				idx = i;
			}
		}
		return t+1+min;
	}
	else if(m>=1){
		return t+n;
	}
}
int main(){
	int n;
	cin>>n;
	
	cout<<solve(n,0,100);
}
