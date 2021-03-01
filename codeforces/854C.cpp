#include <iostream>
#include <algorithm>
#define REP(i,n) for(int i=0;i<n;i++)
#define X first
#define Y second
using namespace std;
typedef pair<int,int> PI;
bool larger(pair<int,int> i,pair<int,int> j){
	return i.X>j.X;
}
int main(){
	int n,k;
	cin>>n>>k;
	
	pair<int,int> c[n+1];
	int d[n+1]={};
	REP(i,n){
		cin>>c[i].X;
		c[i].Y=i+1;
	}
	
	sort(c,c+n,greater<PI>());
	

	
	
	int cost=0;
	//c[i].X 是價格係數 c[i].Y 是班機順序 
	for(int i=k+1;i<k+n+1;i++){  //I是時間 
		int j;
		for(j=0;(d[c[j].Y-1]!=0||c[j].Y>i)&&j<n;j++);
		cost += c[j].X * (i-c[j].Y);
		d[c[j].Y-1] = i;
	}
	
	cout<<cost<<endl;
	REP(i,n)
		cout<<d[i]<<" \n"[(i==n-1)];
	
	
}
