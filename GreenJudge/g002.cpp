#include <iostream>
using namespace std;

int main(){
	int a,b,c,d,e,f; //abc player def
	cin>>a>>b>>c>>d>>e>>f;
	while(a){
		bool p = true;
		int rc = 0;
		while(a&&d){
			if(p){
				if(b>f){
					d-=b-f;
					if(d<0)d=0;
				}
				rc++;
			}
			else{
				if(e>c){
					a-=e-c;
					if(a<0)a=0;
				}
			}
			p=!p;
		}
		if(p){
			cout<<"You lose in "<<rc<<" round(s)."	<<endl;
		}
		else{
			cout<<"You win in "<<rc<<" round(s)."<<endl;
		}
		cin>>a>>b>>c>>d>>e>>f;
	}
}
