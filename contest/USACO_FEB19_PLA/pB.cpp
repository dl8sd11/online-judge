#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) ll(i.size())
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
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
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll MAXN = 1503;
ll n,m,x,y;
vector<ll> len[MAXN];
ll lensz;
vector<pii> edge[MAXN];
bitset<MAXN> vis;

ll cc[MAXN],ccsz;
void dfs(ll nd,ll par) {
    vis[nd] = true;
    cc[ccsz++] = nd;
    for (auto v : edge[nd]) {
        if (v.X != par) {
            dfs(v.X,nd);
        }
    }
}

void dfs2(ll nd,ll par,ll dis) {
    if (nd != par) {
        len[lensz].eb(dis);
    }
    for (auto v : edge[nd]) {
        if (v.X != par) {
            dfs2(v.X,nd,dis+v.Y);
        }
    }
}
ll dp[2][2503],cnt[MAXN][2503];
/********** Good Luck :) **********/
int main()
{
#ifndef tmd
    freopen("mooriokart.in","r",stdin);
    freopen ("mooriokart.out","w",stdout);
#endif
    cin >> n >> m >> x >> y;
    REP (i,m) {
        ll u,v,w;
        cin >> u >> v >> w;
        edge[u].emplace_back(v,w);
        edge[v].emplace_back(u,w);
    }

    REP1 (i,n) {
        if (!vis[i]) {
            ccsz = 0;
            dfs(i,i);
            REP (j,ccsz) {
                dfs2(cc[j],cc[j],0);
            }
            lensz++;
        }
    }
    pary(len,len+lensz);

    ll *dpcur = &dp[0][0];
    ll *dpnxt = &dp[1][0];
    ll *cntcur = &cnt[0][0];
    ll *cntnxt = &cnt[1][0];

    cntcur[0] = 1;
    REP (i,lensz) {
        REP (j,y+1) {
            cntnxt[j] = 0;
        }
        REP (j,y+1) {
            for (auto l : len[i]) {
                if (cntcur[j]) {
                    cntnxt[min(y,j+x+l)] += cntcur[j];
                    cntnxt[min(y,j+x+l)] %= MOD;
                    dpnxt[min(y,j+x+l)] += dpcur[j]+(l+x)*cntcur[j]%MOD;
                    dpnxt[min(y,j+x+l)] %= MOD;
                }
            }
        }
        swap(dpcur,dpnxt);
        swap(cntcur,cntnxt);
    }


    dpcur[y] *= 500000004;
    dpcur[y] %= MOD;

    REP1 (i,lensz-1) {
        dpcur[y] *= i;
        dpcur[y] %= MOD;
    }    
    cout << dpcur[y] << endl;
    return 0;
}
