#include <iostream>
using namespace std;

int main(){
	int ct;
	cin>>ct;
	for(int i=0;i<ct;i++){
		int v;
		int ans=0;
		cin>>v;
		while(v/27!=0){
			v-=27;
			ans++;
		}
		while(v/9!=0){
			v-=9;
			ans++;
		}
		while(v/3!=0){
			v-=3;
			ans++;
		}
		ans+=v;
		cout<<ans<<endl;
	} 
	
}

//ac
