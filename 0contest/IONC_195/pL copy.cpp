#include  <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
 typedef long long ll;
using namespace std;
 
 
const int maxn=66666;
const double eps=1e-8;
 
int sgn(double x)
{
    if(fabs(x)<eps)
        return 0;
    if(x<0)
        return -1;
    else
        return 1;
}
struct Point
{
    double x,y;
    Point(){}
    Point(ll _x,ll _y)
    {
        x=_x;
        y=_y;
    }
    Point operator -(const Point &b)const
    {
        return Point(x-b.x,y-b.y);
    }
    ll operator ^(const Point &b)const
    {
        return x*b.y-y*b.x;
    }
    ll operator *(const Point &b)const
    {
        return x*b.x+y*b.y;
    }
};
 
Point p[maxn];
int n;
int Stack[maxn];
int top;
 
ll dist(Point a,Point b)
{
    return (a-b)*(a-b);
}
bool cmp(Point a,Point b)
{
    int ans=sgn((a-p[0])^(b-p[0]));
    if(ans==1)
        return true;
    else if(ans==0)
        return dist(a,p[0])<dist(b,p[0]);
    else
        return false;
}
 
void graham()
{
    for(int i=0;i<n;i++)
    {
        if(p[i].x<p[0].x||(p[i].x==p[0].x&&p[i].y<p[0].y))
            swap(p[0],p[i]);
    }
    sort(p+1,p+n,cmp);
    if(n==1)
    {
        Stack[0]=0;
        top=1;
    }
    else if(n==2)
    {
        Stack[0]=0;
        Stack[1]=1;
        top=2;
    }
    else
    {
        Stack[0]=0;
        Stack[1]=1;
        top=2;
        for(int i=2;i<n;i++)
        {
            while(top>1&&sgn((p[Stack[top-1]]-p[Stack[top-2]])^(p[i]-p[Stack[top-2]]))<=0)
                top--;
            Stack[top++]=i;
        }
    }
}
Point p1[maxn];
 
ll dist1(Point a,Point b)
{
    return (a-b)*(a-b);
}
ll getarea(Point a,Point b,Point c)
{
    return (b-a)^(c-a);
}
ll rot_all()
{
    
    ll maxz=0;
    int i,j,k,kk;
    for(i=0; i<top; ++i)
    {
        j=(i+1)%top;
        k=(j+1)%top;
        while(k!=i && getarea(p1[i],p1[j],p1[k])<getarea(p1[i],p1[j],p1[k+1]))
            k=(k+1)%top;
        maxz = max(maxz,getarea(p1[i],p1[j],p1[k]));
        if(k == i)
            continue;
        kk=(k+1)%top;
        while(j!=kk && k!=i)
        {
            while(k!=i && getarea(p1[i],p1[j],p1[k])<getarea(p1[i],p1[j],p1[k+1]))
                k=(k+1)%top;
            maxz = max(maxz,getarea(p1[i],p1[j],p1[k]));
            j=(j+1)%top;
        }
    }
    return maxz;
}

 
 
int main()
{
  ios_base::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=0;i<n;i++)
    {
      cin >> p[i].x >> p[i].y;
    }
    graham();
    if(top<3)
      cout << 0 << '\n';
    else
    {
        for(int i=0;i<top;i++)
        {
            p1[i]=p[Stack[i]];
        }
        ll ans;
        ans=rot_all();
        cout << ans << '\n';
    }
    return 0;
}