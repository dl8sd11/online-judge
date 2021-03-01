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
const ll MAXN = 200003;

ll n,k;
vector<pii> edge[MAXN];
vector<pii> deg;

bool pri[MAXN];
ll ans[MAXN];

ll cnt;
void dfs(ll nd,ll par,ll cl) {
    ll idx = 0;
    for (auto v : edge[nd]) {
        if (v.X != par) {
            if (pri[nd]) {
                if (cl == -1) {
                    ans[v.Y] = 1;
                } else {
                    ans[v.Y] = cl;
                }
            } else {
                idx++;
                if (idx == cl) {
                    idx++;
                }
                ans[v.Y] = idx;
            }
            dfs(v.X,nd,ans[v.Y]);
        }
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> k;
    REP (i,n-1) {
        ll u,v;
        cin >> u >> v;
        edge[u].emplace_back(v,i);
        edge[v].emplace_back(u,i);
    }

    REP1 (i,n) {
        deg.emplace_back(SZ(edge[i]),i);
    }

    sort(ALL(deg));

    debug(deg);

    ll idx = 0;
    RREP(i,SZ(deg)-1) {
        if (idx<k) {
            pri[deg[i].Y] = true;
        } else {
            cnt = max(cnt,deg[i].X);
        }
        idx++;
    }
    debug(cnt);
    pary(pri+1,pri+n+1);

    dfs(1,-1,-1);

    cout << cnt << endl;
    REP (i,n-1) {
        cout << ans[i] << " \n"[i==n-2];
    }
    return 0;
}
