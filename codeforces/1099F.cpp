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

ll bit1[MAXN],bit2[MAXN];
void add(ll pos,ll val,ll *bit) {
    for (;pos<MAXN;pos+=-pos&pos) {
        bit[pos] += val;
    }
}

ll query(ll pos,ll *bit) {
    ll ret = 0;
    for (;pos>=1;pos-=-pos&pos) {
        ret += bit[pos];
    }
    return ret;
}

ll n,T,x[MAXN],t[MAXN],dp[MAXN];
vector<pii> edge[MAXN];

void dfs(ll nd,ll dis) {
    add(t[nd],t[nd]*x[nd],bit1);
    add(t[nd],x[nd],bit2);

    ll L = 0,R = MAXN;
    while (L < R - 1) {
        ll mid = (L + R) >> 1;
        if (query(mid,bit1) <= T-dis*2) {
            L = mid;
        } else {
            R = mid;
        }
    }

    ll rem = T - dis*2 - query(L,bit1);
    if (T-dis*2 > 0) {
        dp[nd] = query(L,bit2) + (R < MAXN ?rem / R : 0);
    } else {
        dp[nd] = 0;
    }

    for (auto p : edge[nd]) {
        dfs(p.X,dis+p.Y);
    }

    add(t[nd],-t[nd]*x[nd],bit1);
    add(t[nd],-x[nd],bit2);
}

ll dp2[MAXN];
void dfs2(ll nd) {
    pair<ll,ll> mx;
    for (auto p : edge[nd]) {
        dfs2(p.X);
        if (dp2[p.X] >= mx.X) {
            mx.Y = mx.X;
            mx.X = dp2[p.X];
        } else if (dp2[p.X] >= mx.Y) {
            mx.Y = dp2[p.X];
        }
    }
    dp2[nd] = max(dp[nd],mx.Y);
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> T;
    REP1 (i,n) {
        cin >> x[i];
    }
    REP1 (i,n) {
        cin >> t[i];
    }

    for (ll i=2;i<=n;i++) {
        ll u,w;
        cin >> u >> w;
        edge[u].emplace_back(i,w);
    }
    dfs(1,0);

    dfs2(1);

    ll ans = dp[1];
    for (auto v : edge[1]) {
        ans = max(ans,dp2[v.X]);
    }

    pary(dp+1,dp+n+1);
    pary(dp2+1,dp2+n+1);
    cout << ans << endl;
    return 0;
}
