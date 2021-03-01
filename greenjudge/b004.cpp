#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	int n,m,k;
	cin>>n>>m;
	const int max = n+1;
	int human[max];
	
	memset(human,0,sizeof(human));
	for(int i=1;i<=m;i++){
		cin>>k;
		human[k] = 1;
	}
	for(int j=1;j<=n;j++){
		if(human[j]!=1){
			cout<<j<<" ";
		}
	}
	return 0;	
}
