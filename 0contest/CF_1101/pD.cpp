#include <bits/stdc++.h>
using namespace std;
typedef int ll;
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
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

template<class T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template<class T> using MaxHeap = priority_queue<T>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

const ll MOD=1000000007;
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAXN=500;
const ll MAXLG=__lg(MAXN)+2;

ll n,a[MAXN];
vector<ll> edge[MAXN];
ll dp[MAXN][100];

vector<ll> prime;
vector<ll> division[MAXN];
bool sieve[MAXN];
void linear_sieve() {   
    for (ll i=2;i<MAXN;i++) {
        if (!sieve[i]) {
            prime.eb(i);
        }
        for (ll j=0;j<SZ(prime)&&prime[j]*i<MAXN;j++) {
            sieve[prime[j]*i] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}
ll ans = 1;
void DFS(ll nd,ll par) {
    debug(nd);
    REP (i,SZ(division[nd])) {
        dp[nd][i] = 1;
    }
    for (auto v:edge[nd]) if (v != par) {
        DFS(v,nd);
        REP (i,SZ(division[nd])) {
            ll d = division[nd][i];
            ll l = 0,r = SZ(division[v]);
            while (l < r-1) {
                ll mid = (l+r)>>1;
                if (division[v][mid] >= d) {
                    l = mid;
                } else {
                    r = mid;
                }
            }
            debug(division[v],l);
            if (l != SZ(division[v]) && division[v][l] == d) {
                ans = max(ans,dp[v][l]+dp[nd][i]);
                dp[nd][i] = max(dp[v][l]+1,dp[nd][i]);
            }
        }
    }

}
/********** Good Luck :) **********/
int main()
{
    IOS();
    linear_sieve();
    debug(prime.size());
    cin >> n;
    REP (i,n) {
        cin >> a[i];
        ll ta = a[i];
        for (ll j=0;j<SZ(prime)&&prime[j]*prime[j]<=a[i];j++) {
            if (ta % prime[j] == 0) {
                division[i].eb(prime[j]);
                while (ta % prime[j] == 0) {
                    ta /= prime[j];
                }
            }
        }
        if (ta != 1) {
            division[i].eb(ta);
        }
        sort(ALL(division[i]));
    }
    pary(division,division+n);

    REP (i,n-1) {
        ll u,v;
        cin >> u >> v;
        u--,v--;
        edge[u].eb(v);
        edge[v].eb(u);
    }

    bool flag = true;
    REP (i,n) {
        if (a[i] != 1) {
            flag = false;
        }
    }

    if (flag) {
        cout << 0 << endl;
        return 0;
    }
    DFS(0,0);

    cout << ans << endl;
    return 0;
}
