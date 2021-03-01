#include <iostream>
using namespace std;

int main(){
	int ct;
	cin>>ct;
	while(ct!=0){	
		int ls=0;
		int ans=0;
		for(int i=0;i<ct;i++){
			int fl;
			cin>>fl;
			
			if(i!=0){
				if(fl-ls>0)ans+=(fl-ls)*20;
				else ans+=(ls-fl)*10;
			}
			ls=fl;
		}
		cout<<ans<<endl;
		cin>>ct;
	}
	
	
}

//ac
