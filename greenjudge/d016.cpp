#include <iostream>
#include <string>
#include <cmath>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

void printPos(int x,int y){
	cout<<"("<<x<<","<<y<<")";
	if(x==0&&y==0)
		cout<<"在原點"<<endl;
	else if(x==0)
		cout<<"在Y軸"<<endl;
	else if(y==0)
		cout<<"在X軸"<<endl;
	else if(x>0){
		if(y>0)
			cout<<"在第一象限"<<endl;
		else
			cout<<"在第四象限"<<endl;
	}
	else{
		if(y>0)
			cout<<"在第二象限"<<endl;
		else
			cout<<"在第三象限"<<endl;
	}
}
int main(){
	int x,y;
	cin>>x>>y;
	printPos(x,y);
}

