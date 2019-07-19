#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
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
const int iNF = 0x3f3f3f3f;
const ll MAXN = 200005;

int n, siz[MAXN], sod[MAXN], sev[MAXN];
ll V[MAXN], ans;
vector<int> edge[MAXN];

void build(int nd, int par) {
    siz[nd] = sev[nd] = 1;
    for (auto v : edge[nd]) {
        if (v != par) {
            build(v, nd);
            sev[nd] += sod[v];
            sod[nd] += sev[v];
            siz[nd] += siz[v];
        }
    }
}

void norm(ll &x) {
    x = (x % MOD + MOD);
    if (x >= MOD) {
        x -= MOD;
    }
}
void dfs(int nd, int par,int odd, int eve) {
    ll rate = ((eve - odd) * ll(siz[nd]) + siz[1]) % MOD;
    
    debug(nd, odd, eve);
    for (auto v : edge[nd]) {
        if (v != par) {
            int uod = sod[nd] - sev[v] + odd;
            int uev = sev[nd] - sod[v] + eve;
            dfs(v, nd, uev, uod);

            rate += sod[v] * ll(siz[1] - siz[v]);
            norm(rate -= sev[v] * ll(siz[1] - siz[v]));
        }
    }
    norm(ans += V[nd] * rate);
    debug(nd, rate);
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP1 (i, n) {
        cin >> V[i];
    }

    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    build(1, 1);
    pary(siz+1, siz+1+n);
    pary(sod+1, sod+1+n);
    pary(sev+1, sev+1+n);
    dfs(1, 1, 0, 0);

    cout << ans << endl;
    return 0;
}
