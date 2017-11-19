#include <iostream>
using namespace std;

int main(){
	float x,y,z;
	cin>>x>>y>>z;
	
	if(x==0&&y==0&&z==0)cout<<"此座標點落在原點"<<endl;
	else if(x==0&&y==0)cout<<"此座標點落在z軸上"<<endl;
	else if(z==0&&y==0)cout<<"此座標點落在x軸上"<<endl;	
	else if(x==0&&z==0)cout<<"此座標點落在y軸上"<<endl;
	else cout<<"此座標點不落在原點、x軸、y軸或z軸上"<<endl;
}
