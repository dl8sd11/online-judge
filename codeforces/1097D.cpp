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
// const ll MAXN = 

ll mpow(ll base,ll ep) {
    ep = ep % (MOD - 1);
    ll ret = 1;
    while (ep > 0) {
        if (ep & 1) {
            ret = ret * base % MOD;
        }
        base = base * base % MOD;
        ep >>= 1;
    }
    return ret;
}

ll n, k, dp[10004][51][51];
vector<pii> frac;

void norm(ll &x) {
    x = x % MOD;
    return;
}
/*
    dp[k][i][j] = sum {l=j~mx} dp[k-1][i][l] * (1/l)
 */

ll pw[51], ans;
void dfs(ll idx) {
    if (idx == SZ(frac)) {
        ll cur = 1;
        REP (i, SZ(frac)) {
            norm(cur *= mpow(frac[i].X, pw[i]));
            norm(cur *= dp[k][i][pw[i]]);
        }
        norm(ans += cur);
    } else {
        REP (i, frac[idx].Y + 1) {
            pw[idx] = i;
            dfs(idx + 1);
        }
    }
}

ll inv[102];
/********** Good Luck :) **********/
int main()
{
    IOS();
    REP (i, 102) {
        inv[i] = mpow(i, MOD - 2);
    }

    cin >> n >> k;
    ll tn = n;
    for (ll i=2; i*i <= n;i++) {
        ll cnt = 0;
        while (tn % i == 0) {
            tn /= i;
            cnt++;
        }
        if (cnt) {
            dp[0][SZ(frac)][cnt] = 1;
            frac.eb(i, cnt);
        }

    }
    if (tn > 1) {
        dp[0][SZ(frac)][1] = 1;
        frac.eb(tn, 1);
    }
    debug(frac);

    for (int t=1; t<=k; t++) {
        for (int i=0; i<SZ(frac); i++) {
            for (int j=0; j<=frac[i].Y; j++) {
                for (int l=j; l<=frac[i].Y; l++) {
                    norm(dp[t][i][j] += dp[t-1][i][l] * inv[l+1]);
                }
            }
        }
    }
    debug("dped");

    dfs(0);

    cout << ans << endl;
    return 0;
}
