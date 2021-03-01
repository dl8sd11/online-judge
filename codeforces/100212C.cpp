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
const ll MAXN = 2003;

ll n, a[MAXN], dp[MAXN][MAXN], tr[MAXN][MAXN], p[MAXN];
vector<bool> ans[MAXN];

void gen(ll l, ll r) {
    if (l < r) {
        for (ll i=l;i<=r;i++) {
            if (i <= tr[l][r]) {
                ans[i].eb(0);
            } else {
                ans[i].eb(1);
            }
        }
        gen(l, tr[l][r]);
        gen(tr[l][r]+1, r);
    }
}
/********** Good Luck :) **********/
int main()
{
#ifndef tmd
    freopen("codes.in","r",stdin);
    freopen ("codes.out","w",stdout);
#endif
    cin >> n;
    REP1 (i, n) {
        cin >> a[i];
        p[i] = p[i-1] + a[i];
    }

    MEM(dp, INF);
    REP1 (i, n) {
        dp[i][i] = 0;
        tr[i][i] = i;
    }
    for (ll len=2;len<=n;len++) {
        for (ll l=1;l+len-1<=n;l++) {
            ll r = l + len - 1;
            for (ll t=tr[l][r-1];t<=tr[l+1][r];t++) {
                if (dp[l][t] + dp[t+1][r] < dp[l][r]) {
                    dp[l][r] = dp[l][t] + dp[t+1][r];
                    tr[l][r] = t;
                }
            }
            dp[l][r] += p[r] - p[l-1];
        }
    }

    gen(1, n);
    REP1 (i, n) {
        for (auto b : ans[i]) {
            cout << b;
        }
        cout << endl;
    }
    return 0;
}
