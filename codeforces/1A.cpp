#include <iostream>
typedef long long ll;
using namespace std;
long long unsigned int solve(int x,int y){
	if(x%y==0)
		return x/y;
	else
		return x/y+1;
}
int main(){
	long long unsigned int n,m,a,ans;
	cin>>n>>m>>a;
	ans= solve(n,a)*solve(m,a);
	cout<<ans<<endl;
}
