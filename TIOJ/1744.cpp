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
const ll MAXN = 500005;

int n, m, bk[MAXN], s, p, ccnt, cc[MAXN], sum[MAXN];
bool bar[MAXN], bar_cc[MAXN], vis[MAXN];
vector<int> edge[MAXN], rev[MAXN], g[MAXN];

vector<int> topo;
void dfs1 (int nd) {
    vis[nd] = true;
    for (auto v : rev[nd]) {
        if (!vis[v]) {
            dfs1(v);
        }
    }
    topo.eb(nd);
}

void dfs2 (int nd) {
    vis[nd] = false;
    cc[nd] = ccnt;
    bar_cc[ccnt] |= bar[nd];
    sum[ccnt] += bk[nd];
    for (auto v : edge[nd]) {
        if (vis[v]) {
            dfs2(v);
        } else if (cc[v] != ccnt) {
            g[ccnt].eb(cc[v]);
        }
    }
}

int dp[MAXN];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP (i, m) {
        int f, t;
        cin >> f >> t;
        edge[f].eb(t);
        rev[t].eb(f);
    }
    REP1 (i, n) {
        cin >> bk[i];
    }
    cin >> s >> p;
    REP (i, p) {
        int nd;
        cin >> nd;
        bar[nd] = true;
    }

    REP1 (i, n) {
        if (!vis[i]) {
            dfs1(i);
        }
    }

    debug(topo);
    for (int i=n-1;i >=0; i--) {
        int nd = topo[i];
        if (vis[nd]) {
            dfs2(nd);
            ccnt++;
        }
    }

    MEM(dp, -1);
    REP (i, ccnt) {
        if (bar_cc[i]) {
            dp[i] = sum[i];
        }
        for (auto v : g[i]) {
            debug(i, v);
            if (dp[v] != -1) {
                dp[i] = max(dp[i], sum[i] + dp[v]);
            }
        }
    }
    pary(cc+1, cc+n+1);
    pary(sum, sum+ccnt);
    pary(dp, dp+ccnt);
    
    cout << dp[cc[s]] << endl;
    return 0;
}
