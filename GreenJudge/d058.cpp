#include <iostream>
using namespace std;

int main(){
	float x,y,z;
	cin>>x>>y>>z;
	
	if(x==0&&y==0&&z==0)cout<<"���y���I���b���I"<<endl;
	else if(x==0&&y==0)cout<<"���y���I���bz�b�W"<<endl;
	else if(z==0&&y==0)cout<<"���y���I���bx�b�W"<<endl;	
	else if(x==0&&z==0)cout<<"���y���I���by�b�W"<<endl;
	else cout<<"���y���I�����b���I�Bx�b�By�b��z�b�W"<<endl;
}
