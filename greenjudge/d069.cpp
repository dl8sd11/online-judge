#include <iostream>
using namespace std;
int bg(int *a){
	int lt = a[0];
	int idx=0;
	for(int i=1;i<=2;i++){
		if(a[i]>lt){
			lt=a[i];
			idx=i;
		}
	}
	return idx;
}
int sm(int *a){
	int lt = a[0];
	int idx=0;
	for(int i=1;i<=2;i++){
		if(a[i]<lt){
			lt=a[i];
			idx=i;
		}
	}
	return idx;
}
int main(){
	int a[3];
	cin>>a[0]>>a[1]>>a[2];
	
	int lt = bg(a);
	int sl = sm(a);
	int ans;
	if(a[lt]>a[3-lt-sl]+a[sl])ans=lt;
	else ans=3-lt-sl;
	
	switch(ans){
		case 0:
			cout<<"¥Ò"<<endl;
			break;
		case 1:
			cout<<"¤A"<<endl;
			break;
		case 2:
			cout<<"¤ş"<<endl;
			break;
		default:
			cout<<"error"<<endl;
			break;
	}
	
	
}

//ac
