#include <iostream>
typedef long long ll;
using namespace std;

int main(){
	int n;
	cin>>n;
	const int max = n;
	int b[max][2];
	int ct=0;
	for(int i=0;i<n;i++){
		int tmp;
		cin>>tmp;
		bool flag = true;
		for(int j=0;j<ct;j++){
			if(b[j][1]==tmp){
				b[j][0]++;
				flag = false;
				break;
			}
		}
		if(flag){
			b[ct][1]=tmp;
			b[ct][0]=1;
			ct++;
		}
	}
	
	int maxIdx = 0;
	for(int i=1;i<ct;i++){
		if(b[i][0]>b[maxIdx][0]){
			maxIdx = i;
		}
	}
	cout<<b[maxIdx][1]<<" "<<b[maxIdx][0]<<endl;
}

