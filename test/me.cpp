#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
const int maxn=1e6+7;
const int inf=INT_MAX;
const ll inff=1e18;
const ll mod=1e9+7;
#define pii pair<int,int>
#define mkp make_pair
#define F first
#define S second
#define pb push_back
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(),(v).end()
#define int ll
 
#ifdef HNO2
#define IOS
#else
#define endl '\n'
#define IOS ios::sync_with_stdio(0); cin.tie(0);
#endif // HNO2
 
int n,w,x,y;
int l[maxn],r[maxn];
vector<int> v[maxn],cl[maxn],cr[maxn];
multiset<int> m[maxn];
int ans[maxn],maxx[maxn];
 
int changer(int p)
{
    int ret=-maxx[p];
    m[p].insert(v[p][++r[p]]);
    maxx[p]=(*(--m[p].end()));
    ret+=maxx[p];
    return ret;
}
 
int changel(int p)
{
    int ret=-maxx[p];
    if (l[p]!=-1) m[p].erase(m[p].find(v[p][l[p]]));
    l[p]++;
    maxx[p]=(*(--m[p].end()));
    ret+=maxx[p];
    return ret;
}
 
int32_t main()
{
    IOS
    cin>>n>>w;
    for (int i=1;i<=n;i++) l[i]=-1ll,r[i]=-1ll,m[i].insert(0ll);
    for (int i=1;i<=n;i++)
    {
        cin>>x;
        for (int j=0;j<x;j++)
        {
            cin>>y;
            v[i].pb(y);
        }
        for (int j=1;j<=x;j++) cr[j].pb(i);
        for (int j=w;j>w-x;j--) cl[j].pb(i);
    }
    for (int i=1;i<=w;i++)
    {
        ans[i]=ans[i-1];
        for (int j:cr[i]) ans[i]+=changer(j);
        for (int j:cl[i]) ans[i]+=changel(j);
    }
    for (int i=1;i<=w;i++) cout<<ans[i]<<" \n"[i==w];
}
 