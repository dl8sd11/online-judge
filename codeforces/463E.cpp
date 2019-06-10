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
const ll MAXC = 2000006;
const ll MAXN = 1000005;

ll n,q,a[MAXN],ans[MAXN],dep[MAXN];
vector<ll> stk[MAXC];
vector<ll> edge[MAXN];

bool sieve[2003];
vector<ll> prime;
void linear_sieve() {
    for (ll i=2; i*i < MAXC; i++) {
        if (!sieve[i]) {
            prime.eb(i);
        }
        for (ll j=0; j<SZ(prime) && i*prime[j] < 2003; j++) {
            sieve[i*prime[j]] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}

void dfs(ll nd,ll par) {
    if (nd == par) {
        dep[nd] = 0;
    } else {
        dep[nd] = dep[par] + 1;
    }

    vector<ll> prime_div;
    ll val = a[nd];
    pair<ll,ll> ret = {-1,-1};
    for (auto v : prime) {
        if (val % v == 0) {
            prime_div.eb(v);
            if (!stk[v].empty() && dep[stk[v].back()] > ret.Y) {
                ret.X = stk[v].back();
                ret.Y = dep[ret.X];
            }
            stk[v].eb(nd);   
        }
        while (val % v == 0) {
            val /= v;
        }
    }
    if (val != 1) {
        prime_div.eb(val);
        if (!stk[val].empty() && dep[stk[val].back()] > ret.Y) {
                ret.X = stk[val].back();
                ret.Y = dep[ret.X];
            }
        stk[val].eb(nd);
    }
    ans[nd] = ret.X;

    for (auto v : edge[nd]) {
        if (v != par) {
            dfs(v,nd);
        }
    }

    for (auto v : prime_div) {
        stk[v].pop_back();
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    linear_sieve();

    cin >> n >> q;
    REP1 (i,n) {
        cin >> a[i];
    }
    REP (i,n-1) {
        ll u,v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    dfs(1,1);
    while (q--) {
        ll cmd;
        cin >> cmd;
        if (cmd == 1) {
            ll v;
            cin >> v;
            cout << ans[v] << endl;
        } else {
            ll v,w;
            cin >> v >> w;
            a[v] = w;
            dfs(1,1);
        }
    }
    return 0;
}
