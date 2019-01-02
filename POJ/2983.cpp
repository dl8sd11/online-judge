#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstring>
#include<bitset>
#include<string>
#include<set>
#include<map>
#include<vector>
#include<algorithm>
#include<sstream>
#include<cmath>
#include<queue>
#include<stack>
#include<list>
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


const ll MAXN=1005;
const ll MOD=1000000007;
const ll INF=0x3f3f3f3f;


struct E {
    ll t,w,next;
}edge[200003];
ll tot;

ll n,m;
ll head[MAXN],cnt[MAXN],dis[MAXN];
bool vis[MAXN];

void add_edge(ll f,ll t,ll w) {
    edge[tot].t = t;
    edge[tot].w = w;
    edge[tot].next = head[f];
    head[f] = tot++;
} 
int main()
{
    IOS();
    while (cin>>n>>m) {
        MEM(head,-1);
        tot = 0;
        char cmd[5];
        bool flag = 0;
        ll a,b,x;
        REP (i,m) {
            cin>>cmd;
            if (cmd[0] == 'P') {
                cin>>a>>b>>x;
                if (a == b && x != 0) {
                    flag = true;
                }
                add_edge(a,b,x);
                add_edge(b,a,-x);
            } else {
                cin>>a>>b;
                if (a == b) {
                    flag = true;
                }
                add_edge(a,b,1);
            }
        }
        if (flag) {
            cout << "Unreliable" << endl;
            continue;
        }


        MEM(cnt,0);
        MEM(vis,0);
        MEM(dis,0);
        queue<ll> qu;
        REP1 (i,n) {
            qu.push(i);
        }
        while (qu.size()) {
            ll cur = qu.front();qu.pop();
            if (cnt[cur] > n+3) {
                flag = 1;
                break;
            }
            vis[cur] = false;
            for (ll i=head[cur];i!=-1;i=edge[i].next) {
                if (dis[edge[i].t] < dis[cur] + edge[i].w) {
                    dis[edge[i].t] = dis[cur] + edge[i].w;
                    if (!vis[edge[i].t]) {
                        qu.push(edge[i].t);
                        vis[edge[i].t] = true;
                        cnt[edge[i].t] ++;
                    }
                }
            }
        }

        if (flag) {
            cout << "Unreliable" << endl;
        } else {
            cout << "Reliable" << endl;
        }
    }
}
