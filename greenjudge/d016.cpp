#include <iostream>
#include <string>
#include <cmath>
#define REP(i,n) for(int i=0;i<n;i++)
typedef long long ll;
using namespace std;

void printPos(int x,int y){
	cout<<"("<<x<<","<<y<<")";
	if(x==0&&y==0)
		cout<<"�b���I"<<endl;
	else if(x==0)
		cout<<"�bY�b"<<endl;
	else if(y==0)
		cout<<"�bX�b"<<endl;
	else if(x>0){
		if(y>0)
			cout<<"�b�Ĥ@�H��"<<endl;
		else
			cout<<"�b�ĥ|�H��"<<endl;
	}
	else{
		if(y>0)
			cout<<"�b�ĤG�H��"<<endl;
		else
			cout<<"�b�ĤT�H��"<<endl;
	}
}
int main(){
	int x,y;
	cin>>x>>y;
	printPos(x,y);
}

