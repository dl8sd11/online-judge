#include<bits/stdc++.h>
using namespace std;
const int N=100055;
int n,q,dfn,ll[N],id[N],dep[N],fa[N][22],mx[N][22],mn[N][22],lg[N];
vector<int>G[N];
void dfs(int x,int p)
{
	ll[x]=++dfn;id[dfn]=x;fa[x][0]=p;
	for(int j=1;j<=20;j++)fa[x][j]=fa[fa[x][j-1]][j-1];
	for(int i=0;i<G[x].size();i++)dep[G[x][i]]=dep[x]+1,dfs(G[x][i],x);
}
void rmq()
{
	for(int i=2;i<=n;i++)lg[i]=lg[i>>1]+1;
	for(int i=1;i<=n;i++)mx[i][0]=mn[i][0]=ll[i];
	for(int i=1;i<=20;i++)for(int j=1;j+(1<<i-1)<=n;j++)mx[j][i]=max(mx[j][i-1],mx[j+(1<<i-1)][i-1]);
	for(int i=1;i<=20;i++)for(int j=1;j+(1<<i-1)<=n;j++)mn[j][i]=min(mn[j][i-1],mn[j+(1<<i-1)][i-1]);
}
int gtmn(int l,int r){int d=lg[r-l+1];return min(mn[l][d],mn[r-(1<<d)+1][d]);}
int gtmx(int l,int r){int d=lg[r-l+1];return max(mx[l][d],mx[r-(1<<d)+1][d]);}
int lca(int u,int v)
{
	if(dep[u]<dep[v])swap(u,v);
	int sub=dep[u]-dep[v];
	for(int i=0;i<=20;i++)if(sub>>i&1)u=fa[u][i];
	if(u==v)return u;
	for(int i=20;i>=0;i--)if(fa[u][i]!=fa[v][i])u=fa[u][i],v=fa[v][i];
	return fa[u][0]; 
}
int gt(int x,int l,int r)
{
	int ans1,ans2;
	if(x==l)ans1=gtmn(l+1,r),ans2=gtmx(l+1,r);
	else if(x==r)ans1=gtmn(l,r-1),ans2=gtmx(l,r-1);
	else ans1=min(gtmn(l,x-1),gtmn(x+1,r)),ans2=max(gtmx(l,x-1),gtmx(x+1,r));
	return lca(id[ans1],id[ans2]);
}
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=2,p;i<=n;i++)scanf("%d",&p),G[p].push_back(i);
	dfs(1,0);rmq();
	while(q--)
	{
		int l,r;scanf("%d%d",&l,&r);
		if(n==2){puts("1 1");continue;}
		int ll=gtmn(l,r),rr=gtmx(l,r),f1=gt(id[ll],l,r),f2=gt(id[rr],l,r);
		if(dep[f1]>=dep[f2])printf("%d\n",dep[f1]);else printf("%d\n",dep[f2]);
	}
	return 0;
}