#include <bits/stdc++.h>
using namespace std;

int n,a[103],sum,ans;
char c;
bool solve(int len){
	int cnt = 0,total = 0;
	for(int i=0;i<n;i++){
		total += a[i];
		if(total > len)return false;
		if(total == len)cnt++,total = 0;
	}
	if(cnt>1&&total==0)return true;
	return false;
}

int main(){
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>c,a[i] = c-'0',sum+=a[i];

	if(sum==0&&n>1)ans = 1;

	for(int i=1;i*i<=sum;i++){
		ans |= solve(i) | solve(sum/i);
	}

	cout<<(ans?"YES":"NO")<<endl;
}