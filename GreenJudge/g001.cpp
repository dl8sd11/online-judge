#include <iostream>
using namespace std;

int main(){
	int n,m;
	
	while(cin>>n>>m){
		int mint = max(n,m);
		int tmp;
		int wc =0;
		int w = 1e6;
		for(int i=0;i<30;i++){
			cin>>tmp;
			if(tmp==mint){
				if(w==1e6){
					w=wc;
				}						
			}
			else if(tmp!=0){
				wc++;
			}
				
		}
		
		if(w<=2){
			cout<<"Y"<<endl;
		}
		else{
			cout<<"N"<<endl;
		}
	}
} 
