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
const ll MAXN = 1000003;

ll n,k;
vector<ll> edge[MAXN];
ll dp[MAXN];
ll ans = 0;

void dfs(ll nd,ll par) {
    if (edge[nd].size() == 1) {
        dp[nd] = 0;
        return;
    }

    vector<ll> dis;
    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v,nd);
            if (dp[v] != -1) {
                dis.emplace_back(dp[v]);
            }
        }
    }

    sort(ALL(dis));
    while (SZ(dis) && dis.back() + 1 >= k) {
        dis.pop_back();
        ans++;
        debug(ans,nd);
    }
    
    while (SZ(dis)>1 && dis.back()+dis[SZ(dis)-2]+2>k) {
        dis.pop_back();
        ans++;
    }
    if (SZ(dis)) {
        dp[nd] = dis.back() + 1;
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
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }
    MEM(dp,-1);
    
    srand(time(0));

    vector<ll> nleaf;
    REP1 (i,n) {
        if (SZ(edge[i]) > 1) {
            nleaf.emplace_back(i);
        }
    }

    ll rt = nleaf[rand()%SZ(nleaf)];
    dfs(rt,rt);

    debug(rt);
    pary(dp+1,dp+n+1);

    if (dp[rt] != -1) {
        ans++;
    }

    cout << ans << endl;
    
    return 0;
}
