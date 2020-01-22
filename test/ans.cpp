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
//#define int ll

#ifdef HNO2
#define IOS
#else
#define endl '\n'
#define IOS ios::sync_with_stdio(0); cin.tie(0);
#endif // HNO2

int n,k;
int a[maxn];

int cnt[maxn];
 multiset<int> M;

void Remove(int x)
{
    if (M.find(cnt[x])!=M.end()) M.erase(M.find(cnt[x]));
    cnt[x]--;
    M.insert(cnt[x]);
}

void Add(int x)
{
    if (M.find(cnt[x])!=M.end())  M.erase(M.find(cnt[x]));
    cnt[x]++;
    M.insert(cnt[x]);
}

int check(int x)
{
    memset(cnt,0,sizeof(cnt));
   M.clear();
    for (int i=1;i<=x;i++) Add(a[i]);
    int maxx=(*(--M.end()));
    for (int i=x+1;i<=n;i++)
    {
        Remove(a[i-x]);
        Add(a[i]);
        maxx=max(maxx,(*(--M.end())));
    }
    if (x-maxx<=k) return 1;
    else return 0;
}

int32_t main()
{
    IOS
    cin>>n>>k;
    for (int i=1;i<=n;i++) cin>>a[i];
    int L=1,R=n+1;
    while(R-L>1)
    {
        int mM=(L+R)>>1;
        if (check(mM)) L=mM;
        else R=mM;
    }
    cout<<L<<endl;
}

