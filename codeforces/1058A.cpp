#include <bits/stdc++.h>
using namespace std;

int main(){
	int n, tmp, ret = 0;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>tmp,ret|=tmp;
	cout<<(ret?"HARD":"EASY")<<endl;
}
