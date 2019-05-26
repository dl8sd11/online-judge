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
const ll MAXN = 100003;

/*
    dp[i][0] : white
    dp[i][1] : black
    white:
        dp[i][0] = pi(dp[i][0]*2 + dp[i][1])
        dp[i][1] = chose one black other (dp[i][0] + dp[i][1])
    black:
        dp[i][0] = 0
        dp[i][1] = pi(dp[i][0]*2 + dp[i][1])
*/

ll n,dp[MAXN][3];
vector<ll> edge[MAXN];
bool x[MAXN];

void dfs(ll nd,ll par) {
    debug(nd);
    if (x[nd]) {
        dp[nd][1] = 1;
        for (auto v : edge[nd]) {
            if (v != par) {
                dfs(v,nd);
                dp[nd][1] = dp[nd][1] * (dp[v][0] + dp[v][1]) % MOD;
            }
        }
    } else {
        dp[nd][0] = 1;
        dp[nd][1] = 0;
        if (SZ(edge[nd]) == 1 && nd != par) {
            return;
        }
        ll sz = SZ(edge[nd]);
        vector<ll> pre,pst;
        ll pdt = 1;
        pre.eb(pdt); 
        for (auto v : edge[nd]) {
            if (v != par) {
                dfs(v,nd);
                dp[nd][0] = (dp[nd][0] * (dp[v][0] + dp[v][1])) % MOD;
                pdt = pdt * (dp[v][0] + dp[v][1]) % MOD;
                pre.eb(pdt);
            }
        }
        pdt = 1;
        pst.eb(pdt);
        RREP (i,sz-1) {
            ll v = edge[nd][i];
            if (v != par) {
                pdt = pdt * (dp[v][0]+dp[v][1]) % MOD;
                pst.eb(pdt);
            }
        }
        reverse(ALL(pst));

        debug(pre,pst);
        ll idx = 0;
        REP (i,sz) {
            ll v = edge[nd][i];
            if (v != par) {
                dp[nd][1] = (dp[nd][1] + pre[idx] * pst[idx+1] % MOD * dp[v][1]) % MOD;
                idx++;
            }
        }
    }
}

/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP1 (i,n-1) {
        ll v;
        cin >> v;
        edge[v].eb(i);
        edge[i].eb(v);
    }
    REP (i,n) {
        cin >> x[i];
    }

    dfs(0,0);
    REP (i,n) {
        pary(dp[i],dp[i]+3);
    }
    cout << dp[0][1]<< endl;
    return 0;
}
