#include <iostream>
using namespace std;

int main(){
	int n;
	cin>>n;
	long long unsigned int sum=0;
	for(int i=1;i<=n;i++){
		sum+=i*i*i*15;
	}
	cout<<"F="<<sum<<endl;
}
