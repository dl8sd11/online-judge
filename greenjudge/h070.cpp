#include <iostream>
#include <algorithm>
using namespace std;


int main(){
	int n;
	cin>>n;
	const int MAXn = n;
	
	int a[MAXn];
	for(int i=0;i<MAXn;i++){
		cin>>a[i];
	}
	sort(a[0],a[MAXn-1]);
	for(int i=0;i<MAXn;i++){
		cout<<a[i]<<" "<<endl;
	}
	
}
