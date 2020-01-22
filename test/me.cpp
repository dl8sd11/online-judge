#include<stdio.h>
#include<algorithm>
using namespace std;
long long num[100005],cnt[100005]={0},cnt2[100005]={0};
int main(){
	long long i,j,n,k,ans=0,len=0;
	scanf("%lld%lld",&n,&k);
	for(i=0;i<n;i++)
		scanf("%lld",&num[i]);
	for(i=0,j=-1;i<n&&j<n;){
		while(j<n-1&&j-i+1-ans<=k){
			j++;
			cnt2[cnt[num[j]]]--;
			cnt[num[j]]++;
			cnt2[cnt[num[j]]]++;
			ans=max(ans,cnt[num[j]]);
		}
		if(j==n-1&&j-i+1-ans<=k)
			len=max(len,j-i+1);
		else
			len=max(len,j-i);
		cnt2[cnt[num[i]]]--;
		if(!cnt2[cnt[num[i]]])
			ans--;
		cnt[num[i]]--;
		cnt2[cnt[num[i]]]++;
		i++;
	}
	printf("%lld\n",len);
}



