#include <bits/stdc++.h>
using namespace std;

int n,m,x,y,tmp,mx = -0x3f3f3f3f,mn = 0x3f3f3f3f;
int main(){
	cin>>n>>m>>x>>y;

	for(int i=0;i<n;i++){
		cin>>tmp;
		mx = max(mx,tmp);
	}

	for(int i=0;i<m;i++){
		cin>>tmp;
		mn = min(mn,tmp);
	}

	if(mx<mn&&mx<y&&mn>x){
		cout<<"No War"<<endl;
	} else {
		cout<<"War"<<endl;
	}
}