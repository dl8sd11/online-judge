#include <iostream>
using namespace std;

int main(){
	int n;
	cin>>n;
	const int MAX = n;
	int ch[MAX];
	
	for(int i=0;i<MAX;i++){
		cin>>ch[i];
	}
	
	int maxSum=0;
	int st,ed;
	
	for(int i=0;i<MAX;i++){
		int sum=0;
		int smaxSum=0;
		int tpst,tped;
		for(int j=i;j<MAX;j++){
			sum+=ch[j];
			if(sum>smaxSum){
				smaxSum=sum;	
			}
		}
		if(maxSum<smaxSum){
			maxSum = smaxSum;
		}
	}
	
	cout<<maxSum<<endl;
}
