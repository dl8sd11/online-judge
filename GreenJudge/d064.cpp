#include <iostream>
#include <sstream>
using namespace std;


int main(){
	int a[3];
	for(int i=0;i<3;i++){
		cin>>a[i];
	}
	
	long long unsigned int max=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(j==i)continue;
			stringstream ss;
			ss<<a[i]<<a[j]<<a[3-i-j];
			long long unsigned int tmp;
			ss>>tmp;
			if(tmp>max)max=tmp;
		}
	}

	cout<<max<<endl;
}
