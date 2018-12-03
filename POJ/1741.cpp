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
typedef pair<int,int> pii;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
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


const int MAXN=1e4+5;


int n,k,root,sz[MAXN],bs[MAXN],ans,cur_size,d[MAXN];
bool vis[MAXN];
vector<pii> edge[MAXN];
void get_centroid(int nd,int par) {
    sz[nd] = 1,bs[nd]  = 0;
    pair<int,int> p=edge[nd][0];
    for (int i = 0;i<SZ(edge[nd]);p=edge[nd][++i]) if(p.X != par && !vis[p.X]) {
        get_centroid(p.X,nd);
        sz[nd] += sz[p.X];
        bs[nd] = max(bs[nd],sz[p.X]);
    }
    bs[nd] = max(bs[nd],cur_size - sz[nd]);
    if (bs[nd] < bs[root]) root = nd;
}

vector<int> dep;
void build(int nd,int par) {
    dep.pb(d[nd]);
    pair<int,int> p=edge[nd][0];
    for (int i = 0;i<SZ(edge[nd]);p=edge[nd][++i]) if (p.X != par && !vis[p.X]) {
        d[p.X] = d[nd] + p.Y;
        build(p.X,nd);
    }
}
int pair_cnt(int nd,int base){
    dep.clear();d[nd] = base;
    build(nd,nd);
    sort(ALL(dep));
    int ret = 0;
    for (int l=0,r=SZ(dep)-1;l<r;) {
        if (dep[l] + dep[r] <= k) ret += r - (l++);
        else r--;
    }
    return ret;
}
void solve(int nd) {
    ans += pair_cnt(nd,0);
    vis[nd] = true;
    pair<int,int> p=edge[nd][0];
    for (int i = 0;i<SZ(edge[nd]);p=edge[nd][++i]) if (!vis[p.X]) {
        ans -= pair_cnt(p.X,p.Y);
        bs[0] = cur_size = sz[p.X];
        root = 0;
        get_centroid(p.X,p.X);
        solve(root);
    }
}

int main()
{
    while (scanf("%d%d",&n,&k) == 2) {
        if (!n || !k) break;

        MEM(vis,0);
        REP (i,n+1) {
            edge[i].clear();
        }

        REP (i,n-1) {
            int u,v,l;
            root = scanf("%d%d%d",&u,&v,&l);
            edge[u].pb({v,l});
            edge[v].pb({u,l});
        }

        root = 0;
        bs[0] = cur_size = n;
        get_centroid(1,1);


        ans = 0;
        solve(root);
        printf("%d\n",ans);
    }

    return 0;
}


// Centroid Decomposition