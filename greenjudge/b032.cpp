#include <iostream> 
using namespace std;
int solve(int *sc,int max,int idx,int lgsc){
	int sMax =0;
	if(idx==max-1){
		if(sc[idx]>lgsc)return 1;
		else return 0;
	}
	for(int i=idx+1;i<max;i++){
		if(sc[i]>lgsc){
			int ans = solve(sc,max,i,sc[i]);
			if (ans>sMax)sMax = ans;
		}else{
			return 0;
		}
	}
	return sMax + 1;
}
	
int main(){
	int n;
	cin>>n;
	
	const int max = n;
	
	int sc[max];
	int len[max];
	
	len[0]=1;
	for(int i=0;i<max;i++){
		cin>>sc[i];
	}
	
	int ans=1;
	for(int i=1;i<max;i++){
		int gt = 0;
		for(int j=0;j<i;j++){
			if(sc[j]<sc[i]&&len[j]>gt)gt=len[j];
		}
		gt++;
		len[i]=gt;
		if(gt>ans)ans=gt; 
	}
	
	cout<<ans<<endl;
}

//AC ^^
