#include <iostream>
using namespace std;

int main(){
	long long unsigned int side[3];
	cin>>side[0]>>side[1]>>side[2];
	long long unsigned int maxSide = side[0];
	int maxIndex=0;
	if(side[1]>side[0]){
		maxIndex=1;
		maxSide=side[1];
	}
	if(side[1]<side[2]){
		maxSide=side[2];
		maxIndex=2;
	}
	
	if(maxSide>=side[0]+side[1]+side[2]-maxSide){
		cout<<"無法形成三角形"<<endl;
		return 0;
	}
	
	long long unsigned int sum=0;
	for(int i=0;i<3;i++){
		if(i!=maxIndex)sum+=side[i]*side[i];
	}

	if(maxSide*maxSide ==sum)cout<<"right triangle"<<endl;
	else if(maxSide*maxSide <sum)cout<<"acute triangle"<<endl;
	else cout<<"obtuse triangle"<<endl;
}

//AC
