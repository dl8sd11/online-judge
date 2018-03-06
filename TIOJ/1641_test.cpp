#include<bits/stdc++.h>
#define DB double
#define INF 100000
using namespace std;
const int maxn=10000+10 ;

struct P{int to ; DB dis ;};
struct Q
{
    int id ; DB dis ;
    bool operator < (const Q &rhs) const
    {
        return dis>rhs.dis ;
    }
};

vector<P> v[maxn] ;
priority_queue<Q> pq ;
bool done[maxn] ;
DB d[maxn] ;

DB Dijkstra(int st,int ed)
{
    fill(d,d+maxn,INF) ;
    d[st]=0.0 ; pq.push((Q){st,0}) ;
    while(!pq.empty())
    {
        Q u=pq.top() ; pq.pop() ;
        if(done[u.id]) continue ;
        done[u.id]=1 ;
        for(auto i : v[u.id]) if(d[i.to] > d[u.id]+i.dis)
            d[i.to]=d[u.id]+i.dis , pq.push((Q){i.to,d[i.to]}) ;
    }
    return d[ed] ;
}

int main()
{
    int n,m,st,ed ; scanf("%d%d%d%d",&n,&m,&st,&ed) ;
    while(m--)
    {
        int x,y ; DB dis ;
        scanf("%d%d%lf",&x,&y,&dis) ;
        v[x].push_back((P){y,log10(dis+1)}) ;
    }
    DB ans=Dijkstra(st,ed) ;
    assert(ans!=INF) ;
    int x= int( floor(ans+1e-7)+1e-7 ) ;
    ans-=x ;
    printf("%.2fe+%03d\n",pow(10,ans),x) ;
}
