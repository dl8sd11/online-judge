#include <iostream>
#include <cmath>
using namespace std;

int main(){
	for(int a=10;a<=99;a++){
		bool usedA[10]={};
		usedA[a%10]=1;
		if(usedA[a/10])continue;
		usedA[a/10]=1;
		for(int b=100;b<=999;b++){
			int tmpB=b;
			bool usedB[10];
			for(int i=0;i<10;i++){
				usedB[i]=usedA[i];
			}
			bool flag = false;
			while(tmpB>0){
				if(usedB[tmpB%10]){
					flag = true;
					break;	
				}
				usedB[tmpB%10]=true;
				tmpB/=10;
			}
			if(flag)continue;
			int c=a*b;
			if((int)log10(c)!=4)continue;
			
			while(c>0){
				if(usedB[c%10]){
					flag = true;
					break;	
				}
				usedB[c%10]=true;
				c/=10;
			}
			if(flag)continue;
			cout<<a<<" X "<<b<<" = "<<a*b<<endl;
			
		}
	}
	cout<<endl<<"共9種運算式"<<endl; 
	
}
