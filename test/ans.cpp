#include <bits/stdc++.h>
using namespace std;
 
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'
#define int long long
#define double long double
 
int32_t main()
{
	IOS; 
	int n,q;
	cin>>n>>q;
	int v[n],c[n];
	for(int i=0;i<n;i++)
		cin>>v[i];
	for(int i=0;i<n;i++)
		cin>>c[i];
	while(q--)
	{
		int a,b;
		cin>>a>>b;
		int dp[n+2]={};
		for(int i=0;i<n+2;i++)
			dp[i]=-1e18;
		pair<int,int> max1;pair<int,int>max2;
		max1={-1e13,-1};max2={-1e13,-2};
		int maxi=0;
		for(int i=0;i<n;i++)
		{
			if(dp[c[i]]!=-1e18)
				dp[c[i]]=max(dp[c[i]],dp[c[i]]+a*v[i]);
			if(max1.second!=c[i])
				dp[c[i]]=max(dp[c[i]],max1.first+b*v[i]);
			else
				dp[c[i]]=max(dp[c[i]],max2.first+b*v[i]);
			dp[c[i]]=max(dp[c[i]],b*v[i]);
			if(max1.second==c[i])
				max1.first=dp[c[i]];
			if(max2.second==c[i])
				max2.first=dp[c[i]];
			if(dp[c[i]]>=max1.first && c[i]!=max1.second && c[i]!=max2.second)
			{
				max2=max1;
				max1={dp[c[i]],c[i]};
			}
			else if(dp[c[i]]>max2.first && c[i]!=max1.second && c[i]!=max2.second)
				max2={dp[c[i]],c[i]};
			if(max1.first<max2.first)
			{
				pair<int,int> p1=max1;
				max1=max2;
				max2=p1;
			}
			maxi=max(maxi,dp[c[i]]);
		}
		cout<<maxi<<endl;
	}
}