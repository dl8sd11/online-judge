#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include<sstream>
#include<cmath>
#include<queue>
#include<stack>
using namespace std;
typedef int ll;
typedef pair<ll,ll> pii;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define MEM(i,n) memset(i,n,sizeof i)
#define X first
#define Y second
#define SZ(_a) (int)_a.size()
#define ALL(_a) _a.begin(),_a.end()
#define pb push_back
#ifdef tmd
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<" ,";_do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s,const pair<_a,_b> &_p){return _s<<"("<<_p.X<<","<<_p.Y<<")";}
template<typename It> ostream& _OUTC(ostream &_s,It _ita,It _itb)
{
    _s<<"{";
    for(It _it=_ita;_it!=_itb;_it++)
    {
        _s<<(_it==_ita?"":",")<<*_it;
    }
    _s<<"}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s,vector<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,set<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#endif


const ll MAXN=20005,MAXlg=__lg(MAXN)+2;
const ll MOD=1000000007;
const ll INF=ll(1e18+7);


struct Edge {
    ll u,v,w;
};

bool cmp (const Edge &e1,const Edge &e2) {
    return e1.w > e2.w;
}

ll djs[MAXN],sz[MAXN];

void init(ll si) {
    REP (i,si) {
        djs[i] = i;
        sz[i] = 1;
    }
}

ll fnd(ll x) {
    ll i = x;
    while (i != djs[i]) i = djs[i];
    while (x != djs[x]) djs[x] = i, x = djs[x];
    return i;
}

void uni(ll x,ll y) {
    if (sz[x=fnd(x)] > sz[y=fnd(y)]) swap(x,y);
    djs[x] = y;
    sz[y] += sz[x];
}
ll n,m,r,test_case;
Edge edge[50005];
int main()
{
    
    scanf("%d",&test_case);
    while (test_case--) {
        scanf("%d%d%d",&n,&m,&r);

        REP (i,r) {
            scanf("%d%d%d",&edge[i].u,&edge[i].v,&edge[i].w);
            edge[i].v += n;
        }
        sort(edge,edge+r,cmp);

        init(n+m);
        ll sub = 0;
        REP (i,r) {
            if (fnd(edge[i].u) != fnd(edge[i].v)) {
                uni(edge[i].u,edge[i].v);
                sub += edge[i].w;
            }
        }

        printf("%d\n",10000 * (n + m) - sub);
    }

    return 0;
}
