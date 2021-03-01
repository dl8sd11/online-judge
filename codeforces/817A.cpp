#include <iostream>
#include <string>
#include <cmath>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){
	int x1,y1,x2,y2;
	cin>>x1>>y1>>x2>>y2;
	int x,y;
	cin>>x>>y;
	
	bool flag = false;
	if((x2-x1)%x!=0){
		cout<<"NO"<<endl;
		return 0;
	}
	if((y2-y1)%y!=0){
		cout<<"NO"<<endl;
		return 0;
	}
	int a = abs(((x2-x1)/x)%2);
	int b = abs(((y2-y1)/y)%2);
	if(a!=b){
		cout<<"NO"<<endl;
		return 0;
	}
	
	cout<<"YES"<<endl;
	return 0;
}

