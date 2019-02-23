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


ll n,a[MAXN];
vector<ll> edge[MAXN];
vector<ll> factor[MAXN];

vector<ll> prime;
bool sieve[MAXN];
void linear_sieve() {
    for (ll i=2;i*i<MAXN;i++) {
        if (!sieve[i]) {
            prime.emplace_back(i);
        }
        for (ll j=0;j<SZ(prime)&&i*prime[j]<1000;j++) {
            sieve[i*prime[j]] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}
ll ans = 1;
ll dp[MAXN][10][2];
void dfs(ll nd,ll par) {
    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v,nd);
            REP (i,SZ(factor[nd])) {
                ll j = lower_bound(ALL(factor[v]),factor[nd][i])-factor[v].begin();
                if (j != SZ(factor[v]) && factor[nd][i] == factor[v][j]) {
                    if (dp[v][j][0] >= dp[nd][i][0]) {
                        dp[nd][i][1] = dp[nd][i][0];
                        dp[nd][i][0] = dp[v][j][0];
                    } else if (dp[v][j][0] >= dp[nd][i][1]) {
                        dp[nd][i][1] = dp[v][j][0];
                    }
                }
            }
        }
    }

    REP (i,SZ(factor[nd])) {
        debug(nd,factor[nd][i],dp[nd][i][0],dp[nd][i][1]);
        ans = max(ans,dp[nd][i][0]+dp[nd][i][1]+1);
        dp[nd][i][0]++;
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    linear_sieve();
    cin >> n;

    REP1 (i,n) {
        cin >> a[i];
        ll tmp = a[i];
        for (auto p : prime) {
            if (a[i] % p == 0) {
                factor[i].emplace_back(p);
            }
            while (tmp % p == 0) {
                tmp /= p;
            }
        }
        if (tmp > 1) {
            factor[i].emplace_back(tmp);
        }
    }

    pary(factor+1,factor+1+n);

    REP (i,n-1) {
        ll u,v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    bool all_one = true;
    REP1 (i,n) {
        if (a[i] != 1) {
            all_one = false;
        }
    }

    if (all_one) {
        cout << 0 << endl;
    } else {
        dfs(1,1);
        cout << ans << endl;
    }
    return 0;
}
