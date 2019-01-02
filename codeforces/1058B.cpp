#include <bits/stdc++.h>
using namespace std;

int n,d,m,x,y;
int main(){
	cin>>n>>d>>m;
	for(int i=0;i<m;i++){
		cin>>x>>y;
		if(((x+y>=d)&&(x+y<=2*n-d))&&((x-y>=-d)&&(x-y<=d))){
			cout<<"YES"<<endl;
		} else {
			cout<<"NO"<<endl;
		}
	}
}