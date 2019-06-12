#include <bits/stdc++.h>
using namespace std;
typedef int ll;
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
const ll MAXN = 100005;
const ll K = sqrt(MAXN);

ll n,m,q,ans[MAXN];
map<ll,vector<ll>> edge[MAXN];
vector<ll> color[MAXN];
vector<pii> query[MAXN];
ll bg[MAXN],vis[MAXN];
vector<ll> bnum;

vector<ll> cc[MAXN];
vector<ll> com;

void dfs(ll nd,ll c) {
    com.eb(nd);
    vis[nd] = c;
    for (auto v : edge[nd][c]) {
        if (vis[v] != c) {
            dfs(v,c);
        }
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP (i,m) {
        ll u,v,c;
        cin >> u >> v >> c;
        edge[u][c].eb(v);
        edge[v][c].eb(u);
        color[c].eb(u);
    }

    cin >> q;
    REP (i,q) {
        ll u,v;
        cin >> u >> v;
        query[min(u,v)].eb(max(u,v),i);
    }

    REP1 (i,n) {
        bg[i] = (SZ(query[i]) > K) ? SZ(bnum) : -1;
        bnum.eb(i);
    }

    pary(query+1,query+n+1);
    debug(bnum);

    REP1 (i,m) {
        for (auto v : color[i]) {
            if (vis[v] != i) {
                com.clear();
                dfs(v,i);
                sort(ALL(com));
                for (auto el : com) {
                    if (bg[el] == -1) {
                        for (auto qr : query[el]) {
                            ans[qr.Y] += upper_bound(ALL(com),qr.X) - lower_bound(ALL(com),qr.X); //com.count(qr.X);
                        }
                    } else {
                        for (auto es : com) {
                            cc[bg[el]].eb(es);
                        }
                    }
                }
            }
        }
    }

    REP (i,SZ(bnum)) {
        sort(ALL(cc[i]));
        for (auto qr : query[bnum[i]]) {
            ans[qr.Y] += upper_bound(ALL(cc[i]),qr.X) - lower_bound(ALL(cc[i]),qr.X);
        }
    }

    REP (i,q) {
        cout << ans[i] << endl;
    }
    return 0;
}
