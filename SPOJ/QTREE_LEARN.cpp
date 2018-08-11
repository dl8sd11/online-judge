#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
struct node
{
    int u,v,w;
    int nex;
}eage[20005];

int head[20005],cnt;
int siz[20005],top[20005],son[20005],fa[20005];
int deep[20005],id[20005],idx,Max[50005],val[20005];

void init()
{
    memset(head,-1,sizeof(head));
    cnt=0;
}
void ADD(int u,int v,int w)
{
    eage[cnt].u=u;
    eage[cnt].v=v;
    eage[cnt].w=w;
    eage[cnt].nex=head[u];
    head[u]=cnt++;
}
void build(int u,int l,int r)
{
    if(l==r)
    {
        Max[u]=val[l];
        return ;
    }
    int mid=(l+r)>>1;
    build(u<<1,l,mid);
    build(u<<1|1,mid+1,r);
    Max[u]=max(Max[u<<1],Max[u<<1|1]);
}
void dfs1(int x,int f,int dep)
{
    deep[x]=dep;
    fa[x]=f;
    siz[x]=1;
    son[x]=0;
    for(int i=head[x];i!=-1;i=eage[i].nex)
    {
        int y=eage[i].v;
        if(y==f)continue;
        dfs1(y,x,dep+1);
        siz[x]+=siz[y];
        if(siz[son[x]]<siz[y])
        {
            son[x]=y;
        }
    }
}
void dfs2(int u,int tp)
{
    top[u]=tp;
    id[u]=++idx;
    if(son[u])dfs2(son[u],tp);
    for(int i=head[u];i!=-1;i=eage[i].nex)
    {
        int v=eage[i].v;
        if(v==fa[u]||v==son[u])continue;
        dfs2(v,v);
    }
}
int query(int u,int l,int r,int L,int R)
{
    //cout<<"*"<<l<<" "<<r<<" "<<L<<" "<<R<<endl;
    if(L<=l&&r<=R)return Max[u];
    int mid=(l+r)>>1;
    int ans=0;
    if(L<=mid)ans=max(ans,query(u<<1,l,mid,L,R));
    if(R>mid)ans=max(ans,query(u<<1|1,mid+1,r,L,R));
    return ans;
}
int work(int u,int v)
{
    int tp1=top[u],tp2=top[v];
    //cout<<tp1<<" "<<tp2<<endl;
    int ans=0;
    while(tp1!=tp2)
    {
        if(deep[tp1]<deep[tp2])
        {
            swap(tp1,tp2);
            swap(u,v);///从u往上升
        }
        ans=max(ans,query(1,1,idx,id[tp1],id[u]));
        u=fa[tp1];
        tp1=top[u];
    }
    //cout<<u<<" "<<v<<endl;
    //cout<<deep[u]<<" "<<deep[v]<<endl;
    if(u==v)return ans;
    if(deep[u]>deep[v])swap(u,v);
    //cout<<id[son[u]]<<" "<<id[v]<<endl;
    ans=max(ans,query(1,1,idx,id[son[u]],id[v]));
    return ans;
}
void change(int u,int l,int r,int pos,int c)
{
    if(l==r&&l==pos)
    {
        Max[u]=c;
        return;
    }
    int mid=(l+r)>>1;
    if(pos<=mid)change(u<<1,l,mid,pos,c);
    else change(u<<1|1,mid+1,r,pos,c);
    Max[u]=max(Max[u<<1],Max[u<<1|1]);
}
int main()
{
    int T;
    scanf("%d",&T);
    int a,b,c;
    while(T--)
    {
        int n;
        scanf("%d",&n);
        init();
        for(int i=1;i<n;i++)
        {
            scanf("%d%d%d",&a,&b,&c);
            ADD(a,b,c);
            ADD(b,a,c);
        }

        idx=0;
        dfs1(1,0,1);
        dfs2(1,1);
        //cout<<"debug"<<endl;
        for(int i=0;i<cnt;i+=2)
        {
            if(deep[eage[i].u]<deep[eage[i].v])swap(eage[i].u,eage[i].v);
            val[id[eage[i].u]]=eage[i].w;
        }
        build(1,1,idx);
//        for(int i=0;i<=idx;i++)cout<<" "<<val[i];
//        cout<<endl;
        char s[10];
        while(1)
        {
            scanf("%s",s);
            if(strcmp(s,"DONE")==0)break;
            scanf("%d%d",&a,&b);
            if(s[0]=='Q')
            {
                printf("%d\n",work(a,b));
            }
            else if(s[0]=='C')
            {
                a--;
                change(1,1,idx,id[eage[2*a].u],b);
            }
        }
        cout<<endl;
    }
    return 0;
}
