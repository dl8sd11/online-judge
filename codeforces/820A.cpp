#include <iostream>
#include <string>
#include <cmath>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

int main(){
	int c,v0,v1,a,l;
	cin>>c>>v0>>v1>>a>>l;
	int maxC = c;
	int days = 1;
	c-=v0;
	if(c<=0){
		cout<<"1"<<endl;
		return 0;
	}
	while(c>0){
		
		v0+=a;
		if(v0>v1)
			v0=v1;
		c+=l;
		if(c>maxC)
			c=maxC;
		c-=v0;
		days++;
	}
	cout<<days<<endl;
	
}

