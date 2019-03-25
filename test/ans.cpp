#include<bits/stdc++.h>
#define N 200009
using namespace std;

int n,m,sz,cnt,tot,l,r,a[N],a0[N],s[N],g[N],ans[N];
map<int,int> mp;
struct node{ int k,x,y; }b[N],p[N];
bool cmp(node u,node v){
	return u.x/sz<v.x/sz || u.x/sz==v.x/sz && u.y/sz<v.y/sz || u.x/sz==v.x/sz && u.y/sz==v.y/sz && u.k<v.k;
}
void ins(int x,int y){
	g[s[x]]--; g[s[x]+=y]++;
}
void mdy(int x,int y){
	if (l<=x && x<=r){
		ins(a[x],-1); ins(y,1);	
	}
	a[x]=y; 
}
int main(){
	scanf("%d%d",&n,&m);
	sz=ceil(pow(n,2./3));
	int i,j;
	for (i=1; i<=n; i++){
		scanf("%d",&a[i]);
		if (!mp[a[i]]) mp[a[i]]=++cnt;
		a[i]=a0[i]=mp[a[i]];	
	}
	for (i=1; i<=m; i++){
		scanf("%d%d%d",&p[i].k,&p[i].x,&p[i].y);
		if (p[i].k==1){
			b[++tot]=p[i]; b[tot].k=i;
		} else{
			if (!mp[p[i].y]) mp[p[i].y]=++cnt;
			p[i].y=mp[p[i].y];
		}
	}
	sort(b+1,b+tot+1,cmp);
	int k=0; l=1;
	for (i=1; i<=tot; i++){
		while (l>b[i].x) ins(a[--l],1); while (r<b[i].y) ins(a[++r],1);
		while (l<b[i].x) ins(a[l++],-1); while (r>b[i].y) ins(a[r--],-1);
		if (b[i].k<k){
			k=0;
			for (j=1; j<=n; j++) mdy(j,a0[j]);	
		}
		for (; k<b[i].k; k++) if (p[k].k==2) mdy(p[k].x,p[k].y);
		for (j=1; g[j]; j++);
		ans[b[i].k]=j;
	}
	for (i=1; i<=m; i++) if (ans[i]) printf("%d\n",ans[i]);
	return 0;
}