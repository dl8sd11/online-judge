#include <iostream>
#include <iomanip>
using namespace std;

int main(){
	int ar[5];
	for(int i=0 ;i<5;i++){
		cin>>ar[i];
	}
	int max = 0;
	int maxIndex =0;
	for(int i=0;i<5;i++){
		if(max<ar[i]){
			max = ar[i];
			maxIndex = i;
		}
	}
	ar[maxIndex]=-5487;
	
	int min = ar[0];
	int minIndex =0;
	for(int i=0;i<5;i++){
		if(ar[i]==-5487)continue;
		if(min>ar[i]){
			min = ar[i];
			minIndex = i;
		}
	}
	ar[minIndex]=-5487;
	float sum=0;
	for(int i=0 ;i<5;i++){
		if(ar[i]!=-5487){
			sum+=ar[i];
		}
	}
	sum = sum/3;
	cout<<fixed<<setprecision(2)<<sum<<endl;
}

//AC
