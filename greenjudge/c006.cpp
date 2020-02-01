#include <iostream>
using namespace std;

int main(){
	int ct;
	cin>>ct;
	
	const int MAX = ct;
	
	int left,right;
	int l[MAX],r[MAX];
	int lc=1;
	int rc=1;
	cin>>left;
	cin>>right;
	l[0]=1;
	r[0]=2;
	for(int i=2;i<ct;i++){
		int tmp;
		cin>>tmp;
		if(left<=right){
			left = left + 10 + tmp;
			l[lc]=i+1;
			lc++;
			
		}
		else{
			right+= 10 + tmp;
			r[rc]=i+1;
			rc++;
		}
	}
	
	for(int i=0;i<lc;i++)cout<<l[i]<<" ";
	cout<<left<<endl;
	for(int i=0;i<rc;i++)cout<<r[i]<<" ";
	cout<<right<<endl;
	
}
