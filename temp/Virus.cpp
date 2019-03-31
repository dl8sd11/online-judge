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
const ll MAXN = 400002;
const ll MAXLG = __lg(MAXN) + 2;

ll n,f[MAXN],q,mx[MAXN][MAXLG],anc[MAXN][MAXLG];
vector<ll> edge[MAXN];

void dfs(ll nd,ll par) {
    anc[nd][0] = par;
    mx[nd][0] = f[par];
    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v,nd);
        }
    }
}

void build() {
    REP1 (i,MAXLG-1) {
        REP1 (j,n) {
            anc[j][i] = anc[anc[j][i-1]][i-1];
            mx[j][i] = max(mx[j][i-1],mx[anc[j][i-1]][i-1]);
        }
    }
}

ll dp[MAXN],ans;
void solve(ll nd,ll par) {
    ll p = nd;
    for (ll i=MAXLG-1;i>=0;i--) {
        if (mx[p][i] <= f[nd]) {
            p = anc[p][i];
        }
    }
    p = anc[p][0];
    dp[nd] = dp[p] + 1;
    ans += dp[nd];

    for (auto v : edge[nd]) {
        if (v != par) {
            solve(v,nd);
        }
    }
}

ll deg[MAXN];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (i,n) {
        cin >> f[i];
    }

    REP (i,n-1) {
        ll u,v;
        cin >> u >> v;
        deg[u]++;
        edge[u].eb(v);
        edge[v].eb(u);
    }
    f[MAXN-1] = INF;

    ll rt = -1;
    REP (i,n) {
        if (deg[i] == 0) {
            rt = i;
        }
    }

    dfs(rt,MAXN-1);
    build();


    solve(rt,rt);

    cout << ans << endl;

    cin >> q;
    REP (i,q) {
        ll P;
        cin >> P >> f[i+n];
        anc[n+i][0] = P;
        mx[n+i][0] = f[P];
        REP1 (k,MAXLG-1) {
            anc[i+n][k] = anc[anc[i+n][k-1]][k-1];
            mx[i+n][k] = max(mx[i+n][k-1],mx[anc[i+n][k-1]][k-1]);
        }

        ll p = i+n;
        for (ll j=MAXLG-1;j>=0;j--) {
            if (mx[p][j] <= f[i+n]) {
                p = anc[p][j];
            }
        }
        p = anc[p][0];
        dp[i+n] = dp[p] + 1;
        ans += dp[i+n];
        cout << ans << endl;
    }
    
    return 0;
}


/*

8
1 4 2 5 2 3 5 4
1 3
2 3
4 3
5 1
6 1
7 2
0 6
2
0 100
0 200

*/